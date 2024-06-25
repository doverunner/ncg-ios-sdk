//
//  NCGPlaybackManager.swift
//  PallyCon.Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import UIKit
import AVFoundation
import MediaPlayer


protocol NCGPlaybackDelegate: class {
    
    /// This is called when the internal AVPlayer in NCGPlaybackManager is ready to start playback.
    func playbackManager(_ playbackManager: NCGPlaybackManager, playerReadyToPlay player: AVPlayer)
    
    /// This is called when the internal AVPlayer's currentItem has changed.
    func playbackManager(_ playbackManager: NCGPlaybackManager, playerCurrentItemDidChange player: AVPlayer)
    
    /// This is called when the internal AVPlayer in NCGPlaybackManager is failed to play playback
    func playbackManager(_ playbackManager: NCGPlaybackManager, playerFail player: AVPlayer, ncgContent: NCGContent?, error: Error?)
}

class NCGPlaybackManager: NSObject {
    static let sharedManager = NCGPlaybackManager()
    
    weak var delegate: NCGPlaybackDelegate?
    
    /// The instance of AVPlayer that will be used for playback of NCGPlaybackManager.playerItem.
    private let player = AVPlayer()
    
    /// A Bool tracking if the AVPlayerItem.status has changed to .readyToPlay for the current NCGPlaybackManager.playerItem.
    private var readyForPlayback = false
    
    private let notificationCenter = NotificationCenter.default
    
    /// The `NSKeyValueObservation` for the KVO on \AVPlayerItem.status.
    private var playerItemObserver: NSKeyValueObservation?
    
    /// The `NSKeyValueObservation` for the KVO on \AVURLAsset.isPlayable.
    private var urlAssetObserver: NSKeyValueObservation?
    
    /// The `NSKeyValueObservation` for the KVO on \AVPlayer.currentItem.
    private var playerObserver: NSKeyValueObservation?
    
    /// The AVPlayerItem associated with NCGPlaybackManager.urlAsset
    private var playerItem: AVPlayerItem? {
        willSet {
            /// Remove any previous KVO observer.
            guard let playerItemObserver = playerItemObserver else { return }
            
            playerItemObserver.invalidate()
            
            notificationCenter.removeObserver(self, name: Notification.Name.UIApplicationWillResignActive, object: nil)
            notificationCenter.removeObserver(self, name: Notification.Name.UIApplicationWillEnterForeground, object: nil)
            notificationCenter.removeObserver(self, name: Notification.Name.AVPlayerItemFailedToPlayToEndTime, object: nil)
        }
        
        didSet {
            playerItemObserver = playerItem?.observe(\AVPlayerItem.status, options: [.new, .initial]) { [weak self] (item, _) in
                guard let strongSelf = self else { return }
                
                if item.status == .readyToPlay {
                    if !strongSelf.readyForPlayback {
                        strongSelf.readyForPlayback = true
                        strongSelf.delegate?.playbackManager(strongSelf, playerReadyToPlay: strongSelf.player)
                    }
                } else if item.status == .failed {
                    let error = item.error
                    print("PlayerItem Error: \(String(describing: error?.localizedDescription))")
                    strongSelf.delegate?.playbackManager(strongSelf, playerFail: strongSelf.player, ncgContent: strongSelf.ncgContent, error: error)
                }
            }
            notificationCenter.addObserver(self, selector: #selector(addMovedToBackground), name: Notification.Name.UIApplicationWillResignActive, object: nil)
            notificationCenter.addObserver(self, selector: #selector(handleNoti(noti:)), name: Notification.Name.UIApplicationWillEnterForeground, object: nil)
            notificationCenter.addObserver(self, selector: #selector(playerItemFailedToPlay(_:)), name: Notification.Name.AVPlayerItemFailedToPlayToEndTime, object: nil)
        }
    }
    
    /// The Asset that is currently being loaded for playback.
    private var ncgContent: NCGContent? {
        willSet {
            /// Remove any previous KVO observer.
            guard let urlAssetObserver = urlAssetObserver else { return }
            
            urlAssetObserver.invalidate()
        }
        
        didSet {
            if let ncgContent = ncgContent {
                urlAssetObserver = ncgContent.urlAsset.observe(\AVURLAsset.isPlayable, options: [.new, .initial]) { [weak self] (urlAsset, _) in
                    guard let strongSelf = self, urlAsset.isPlayable == true else { return }
                    print("Play URL : \(urlAsset.url)")
                    strongSelf.playerItem = AVPlayerItem(asset: urlAsset)
                    strongSelf.player.replaceCurrentItem(with: strongSelf.playerItem)
                }
            }
            else {
                playerItem = nil
                player.replaceCurrentItem(with: nil)
                readyForPlayback = false
            }
        }
    }
    
    // MARK: Intitialization
    override private init() {
        super.init()
        
        playerObserver = player.observe(\AVPlayer.currentItem, options: [.new]) { [weak self] (player, _) in
            guard let strongSelf = self else { return }
            
            strongSelf.delegate?.playbackManager(strongSelf, playerCurrentItemDidChange: player)
        }
    }
    
    deinit {
        player.removeObserver(self, forKeyPath: #keyPath(AVPlayer.currentItem))
        /// Remove any KVO observer.
        playerObserver?.invalidate()
    }
    
    @objc func handleNoti(noti: Notification)  {
        print("notie")
        do {
            if (Ncg2Agent.sharedInstance() as! Ncg2Agent).getLocalWebServerInstance().isServerAlive() == false {
                let beforeTime = CMTimeGetSeconds(player.currentTime())
                if ((try (Ncg2Agent.sharedInstance() as! Ncg2Agent).getLocalWebServerInstance()?.start()) != nil) {
//                    NCGPallyConSDKManager.sharedManager.clearPlaybackUrl()
//                    self.ncgContent?.urlAsset = NCGPallyConSDKManager.sharedManager.getPlaybackUrl(ncgContent: self.ncgContent!, remoteNcgFilePath: "", fileSize: 0)!
//                    let playerItem = AVPlayerItem.init(asset: (self.ncgContent?.urlAsset)!)
//                    player.replaceCurrentItem(with: playerItem)
//                    player.seek(to: CMTimeMakeWithSeconds(beforeTime, Int32(NSEC_PER_SEC)))
                }
            }
        } catch {
            print("Error : \(error)")
        }
    }
    
    @objc func playerItemFailedToPlay(_ noti: Notification) {
        let error = noti.userInfo?[AVPlayerItemFailedToPlayToEndTimeErrorKey] as? Error
        print("playerItemFailedToPlay Error: \(String(describing: error?.localizedDescription))")
        delegate?.playbackManager(self, playerFail: self.player, ncgContent: self.ncgContent, error: error)
    }
    
    /**
     Replaces the currently playing `NCGContent`, if any, with a new `NCGContent`. If nil
     is passed, `NCGPlaybackManager` will handle unloading the existing `NCGContent`
     and handle KVO cleanup.
     */
    func setNcgContentForPlayback(_ ncgContent: NCGContent?) {
        readyForPlayback = false
        guard ncgContent != nil else {
            //self.ncgContent = nil
            return
        }
  
        self.ncgContent = ncgContent

        // 1. NCG Content check
        if NCGPallyConSDKManager.sharedManager.isNcgContent(ncgContent: ncgContent!) {
            // 2. NCG Content license check And acquire license
            if NCGPallyConSDKManager.sharedManager.licenseCheck(ncgContent: ncgContent!) {
                // 3. NCG Content get local web server playback url
                guard let urlAsset = NCGPallyConSDKManager.sharedManager.getPlaybackUrl(ncgContent: ncgContent!, remoteNcgFilePath: "", fileSize: 0) else {
                    return
                }
                self.ncgContent?.urlAsset = urlAsset
                
                // Specify the object to handle WebServerDelegate.
                NCGPallyConSDKManager.sharedManager.setWebServerDelegate(delegate: self as WebServerDelegate)
                
                // When an iOS device is in AirPlay mode, NCG content will not play on an attached Apple TV unless AirPlay playback is set to mirroring.
                // When an external output is allowed in a content license usesExternalPlaybackWhileExternalScreenIsActive property of the AVPlayer object to TRUE.
                if player.isExternalPlaybackActive == true {
                    // Content license Information Check
                    if NCGPallyConSDKManager.sharedManager.isContentAllowExternalDisplay(ncgContent: ncgContent!) == true {
                        // The default value of this property is false.
                        // The value of this property has no effect if allowsExternalPlayback is false.
                        player.usesExternalPlaybackWhileExternalScreenIsActive = true
                    }
                }
            } else {
                print("license expire or No license or license acqure error...")
                let alertController = UIAlertController(title: "Error", message: "license expire or No license or license acqure error. \n Do you want to delete the licence?", preferredStyle: .alert)
                
                let okAction = UIAlertAction(title: "OK", style: UIAlertActionStyle.destructive){ (action: UIAlertAction) in
                    
                    NCGPallyConSDKManager.sharedManager.removeLicense(ncgContent: ncgContent!)
                    print("If the licence for the NCG Content ID is stored, it is deleted.")
                }
                let close = UIAlertAction(title: "Cancel", style: .destructive, handler: nil)
                alertController.addAction(okAction)
                alertController.addAction(close)
                UIApplication.shared.keyWindow?.rootViewController?.present(alertController, animated: true, completion: nil)
                return
            }
        } else {
            // Non DRM Content
            print("Not NCG content")
            if (ncgContent?.downloaded)! {
                self.ncgContent?.urlAsset = AVURLAsset(url: URL(string: (ncgContent?.localPath)!)!)
            }
        }
    }
    
    @objc func addMovedToBackground() {
        readyForPlayback = false
    }
}

extension NCGPlaybackManager: WebServerDelegate {
    func onNotification(_ notificationCode: Int32, notifyMessage: String!) {
        print("Notification : (NCGPlaybackManager) \(notificationCode), \(String(describing: notifyMessage))")
        if notificationCode == 1001 {
            DispatchQueue.main.async {
                let error = NSError(domain: "NCG", code: Int(notificationCode), userInfo: [NSLocalizedDescriptionKey: notifyMessage])
                self.delegate?.playbackManager(self, playerFail: self.player, ncgContent: self.ncgContent, error: error)
                self.playerItem = nil
                self.player.replaceCurrentItem(with: nil)
                self.readyForPlayback = false
            }
        }
    }

func onError(_ errorCode: Int32, errorMessage: String!) {
        print("Error : (NCGPlaybackManager) \(errorCode), \(String(describing: errorMessage))")
    }
    //
    // The local web server checks to see if the player plays the content.
    // If the PlayerStateReadyToPlay value is not returned,
    // the local web server stops decryption and returns the error.
    //
    func onCheckPlayerStatus(_ uri: String!) -> PlayerState {
        var returnValue: Int = 0
        switch (player.currentItem?.status) {
            case .unknown?: returnValue = Int(PlayerStateUnknown.rawValue); break
            case .readyToPlay?: returnValue =  Int(PlayerStateReadyToPlay.rawValue); break
            default: returnValue = Int(PlayerStateFail.rawValue); break
        }
        return PlayerState(rawValue: _PlayerState.RawValue(returnValue))
    }
}
