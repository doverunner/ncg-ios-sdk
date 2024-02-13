//
//  TableViewController.swift
//  PallyCon.Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import UIKit
import AVFoundation
import AVKit

class TableViewController: UITableViewController {
    
    static let playerViewControllerId = "PlayerViewControllerID"
    static let playerViewSegueId = "PlayerViewControllerSegueID"
    
    fileprivate var playerViewController: AVPlayerViewController?
    var avPlayer: AVPlayer?

    var isShowFailedAlertMessage = false

    let downloadService = NCGDownloadManager()
    
    // Create downloadsSession here, to set self as delegate
    lazy var downloadsSession: URLSession = {
        //    let configuration = URLSessionConfiguration.default
        let configuration = URLSessionConfiguration.background(withIdentifier: "bgSessionConfiguration")
        return URLSession(configuration: configuration, delegate: self, delegateQueue: nil)
    }()
    
    // Get local file path: download task stores tune here; AV player plays it.
    let documentsPath = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
    func localFilePath(for url: URL) -> URL {
        return documentsPath.appendingPathComponent(url.lastPathComponent)
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        NCGPlaybackManager.sharedManager.delegate = self
        
        // NCG SDK initialize(). Use it only once. Otherwise, a memory leak occurs.
        if NCGPallyConSDKManager.sharedManager.initialize() == false {
            print("Error")
        }
        downloadService.downloadsSession = downloadsSession
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        if playerViewController != nil {
            // Local web server Playback-URL clear.
            playerViewController?.player?.pause()
            playerViewController?.player = nil
            NCGPallyConSDKManager.sharedManager.clearPlaybackUrl()
            NCGPlaybackManager.sharedManager.setNcgContentForPlayback(nil)
            playerViewController = nil
        }
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
// MARK: - Table view data source
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 2
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return NCGContentManager.sharedManager.numberOfContent(section: section)
    }
    
    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        if section == 0 {
            return "HLS"
        } else if section == 1{
            return "MP4"
        } else {
            return "Zip"
        }
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        
        let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
        let cellId = ncgContent.url.hasSuffix("m3u8") == true ? "HLSCell" : "MP4Cell"
        
        let cell = tableView.dequeueReusableCell(withIdentifier: cellId, for: indexPath) as! TableViewCell
        cell.delegate = self
        
        cell.ncgContent = ncgContent
        // IndexPath.section
        cell.setNCGCell(ncgContent: ncgContent, indexPath: indexPath, downloaded: ncgContent.downloaded, download: downloadService.activeDownloads[URL(string: ncgContent.url)!])
        
        return cell
    }
    
    override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        return 60
    }
    
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        if indexPath.section == 1 {
            let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
            if ncgContent.downloaded {
                return true
            }
        }
        
        return false
    }
    
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if indexPath.section == 1 {
            let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
            if ncgContent.downloaded {
                let destinationURL = localFilePath(for: URL(string: ncgContent.url)!)
                print("destinationURL: \(destinationURL)")
                
                let fileManager = FileManager.default
                try? fileManager.removeItem(at: destinationURL)
                
                // Donwload Contents License Remove
                NCGPallyConSDKManager.sharedManager.removeLicense(ncgContent: ncgContent)
                
                NCGContentManager.sharedManager.setNcgContent(ncgContent: ncgContent, downloaded: false)
                
                tableView.reloadData()
            }
        }
    }
    
    override func tableView(_ tableView: UITableView, accessoryButtonTappedForRowWith indexPath: IndexPath) {
        guard let cell = tableView.cellForRow(at: indexPath) as? TableViewCell,
            let ncgContent = cell.ncgContent else {
                return
        }
        
        if !ncgContent.downloaded {
            if !Recharbility.isConnectedToNetwork() {
                let alertController = UIAlertController(title: "License Failed", message: "network connect failed", preferredStyle: .alert)
                
                let okAction = UIAlertAction(title: "확인", style: UIAlertActionStyle.destructive){ (action: UIAlertAction) in
                    print("license info - network connect failed")
                }
                alertController.addAction(okAction)
                UIApplication.shared.keyWindow?.rootViewController?.present(alertController, animated: true, completion: nil)
                
                return
            }
        }
        
        var message: String = String.init()
        var temp: String = String.init()
        if NCGPallyConSDKManager.sharedManager.isNcgContent(ncgContent: ncgContent) {
            let info:Ncg2LicenseInformation = NCGPallyConSDKManager.sharedManager.contentLicenseInfo(ncgContent: ncgContent)!
            
            temp = info.getPlayStartDate().count > 0 ? info.getPlayStartDate() : "Anytime"
            message.append("Start Date: \(String(describing: temp))\n")
            temp = info.getPlayEndDate().count > 0 ? info.getPlayEndDate() : "Anytime"
            message.append("End Date  : \(String(describing: temp))\n")
            temp = info.getPlayTotalCount() == -1 ? "Unlimit" : String(info.getPlayTotalCount())
            message.append("Play Total: \(String(describing: temp))\n")
            temp = info.getPlayRemainCount() == -1 ? "Unlimit" : String(info.getPlayRemainCount())
            message.append("Play Remain: \(String(describing: temp))\n")
            temp = info.getOutputProtectionPermission().getIsExternalDisplayAllow() == true ? "Yes" : "No"
            message.append("External Display: \(String(describing: temp))\n")
            temp = info.getOutputProtectionPermission().getIsJailBreakExternalDisplayAllow() == 1 ? "Yes" : "No"
            message.append("JailBreak Device: \(String(describing: temp))\n")
        } else {
            message = "NO NCG Content!"
        }
        
        let alertController = UIAlertController(title: "License Info",message: message, preferredStyle: UIAlertControllerStyle.alert)
        
        //UIAlertActionStye.destructive 지정 글꼴 색상 변경
        let okAction = UIAlertAction(title: "확인", style: UIAlertActionStyle.destructive){ (action: UIAlertAction) in
            print("Check")
        }
       
        alertController.addAction(okAction)
        
        self.present(alertController,animated: true,completion: nil)
    }
    
    
    override func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        guard let cell = tableView.cellForRow(at: indexPath) as? TableViewCell,
            let ncgContent = cell.ncgContent else {
                return
        }
        
        if !ncgContent.downloaded {
            if Recharbility.isConnectedToNetwork() {
                self.performSegue(withIdentifier: TableViewController.playerViewSegueId, sender: self)
            } else {
                let alertController = UIAlertController(title: "Play Failed", message: "network connect failed", preferredStyle: .alert)
                
                let okAction = UIAlertAction(title: "확인", style: UIAlertActionStyle.destructive){ (action: UIAlertAction) in
                    print("Play - network connect failed")
                }
                alertController.addAction(okAction)
                UIApplication.shared.keyWindow?.rootViewController?.present(alertController, animated: true, completion: nil)
                return
            }
        } else {
            self.performSegue(withIdentifier: TableViewController.playerViewSegueId, sender: self)
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        super.prepare(for: segue, sender: sender)
        
        if segue.identifier == TableViewController.playerViewSegueId {
            guard let indexPath = self.tableView.indexPathForSelectedRow,
                let cell = tableView.cellForRow(at: indexPath) as? TableViewCell,
                let playerViewController = segue.destination as? AVPlayerViewController,
                let ncgContent = cell.ncgContent else {
                    return
            }
            
            if #available(iOS 11.0, *) {
                playerViewController.entersFullScreenWhenPlaybackBegins = true
                playerViewController.exitsFullScreenWhenPlaybackEnds = true
            } 
            self.playerViewController = playerViewController
            
            NCGPlaybackManager.sharedManager.setNcgContentForPlayback(ncgContent)
        }
    }
}

// MARK: - NCGPlaybackDelegate

extension TableViewController: NCGPlaybackDelegate {
    func playbackManager(_ playbackManager: NCGPlaybackManager, playerReadyToPlay player: AVPlayer) {
        player.play()
    }
    func playbackManager(_ playbackManager: NCGPlaybackManager, playerCurrentItemDidChange player: AVPlayer) {
        guard let playerViewController = playerViewController , player.currentItem != nil else { return }
        
        //player.usesExternalPlaybackWhileExternalScreenIsActive = true
        playerViewController.player = player
    }
    func playbackManager(_ playbackManager: NCGPlaybackManager, playerFail player: AVPlayer, ncgContent: NCGContent?, error: Error?) {
        guard let playerViewController = playerViewController , player.currentItem != nil else { return }
        
        var message = ""
        if error != nil {
            print("Error: \(error!)\n Could play the NCG content")
            message.append("Error: \(error!)\n Could play the NCG content")
        }
        
        let alert = UIAlertController(title: "Play Failed", message: message, preferredStyle: .alert)
        alert.addAction(UIAlertAction(title: "Ok", style: UIAlertActionStyle.default) { Void in
            playerViewController.dismiss(animated: true, completion: nil)
            self.isShowFailedAlertMessage = false
            }
        )
        
        if !isShowFailedAlertMessage {
            playerViewController.present(alert, animated: true, completion: nil)
            isShowFailedAlertMessage = true
        }
    }
}

// MARK: - TableViewCellDelegate
extension TableViewController: TableViewCellDelegate {
    func pauseTapped(_ cell: TableViewCell) {
        if let indexPath = tableView.indexPath(for: cell) {
            let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
            downloadService.pauseDownload(ncgContent)
            reload(indexPath)
        }
    }
    
    func resumeTapped(_ cell: TableViewCell) {
        if let indexPath = tableView.indexPath(for: cell) {
            let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
            downloadService.resumeDownload(ncgContent)
            reload(indexPath)
        }
    }
    
    func cancelTapped(_ cell: TableViewCell) {
        if let indexPath = tableView.indexPath(for: cell) {
            let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
            downloadService.cancelDownload(ncgContent)
            reload(indexPath)
        }
    }
    
    
    func downloadTapped(_ cell: TableViewCell) {
        if let indexPath = tableView.indexPath(for: cell) {
            let ncgContent = NCGContentManager.sharedManager.ncgContent(indexPath: indexPath)
            downloadService.statDownload(ncgContent)
            reload(indexPath)
        }
    }
    // Update NCG Content cell's buttons
    func reload(_ indexPath: IndexPath) {
        DispatchQueue.main.async {
            self.tableView.reloadData()
        }
    }
}
