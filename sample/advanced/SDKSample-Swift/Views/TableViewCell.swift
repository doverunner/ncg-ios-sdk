//
//  TableViewCell.swift
//  PallyCon.Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import UIKit
import AVFoundation
import AVKit

protocol TableViewCellDelegate: class {
    func pauseTapped(_ cell: TableViewCell)
    func resumeTapped(_ cell: TableViewCell)
    func cancelTapped(_ cell: TableViewCell)
    func downloadTapped(_ cell: TableViewCell)
}

class TableViewCell: UITableViewCell {
    
    @IBOutlet weak var contentNameLabel: UILabel!
    @IBOutlet weak var contentDescription: UILabel!
    @IBOutlet weak var downloadButton: UIButton!
    @IBOutlet weak var progressView: UIProgressView!
    @IBOutlet weak var progressLabel: UILabel!
    @IBOutlet weak var pauseButton: UIButton!
    @IBOutlet weak var cancelButton: UIButton!
    
    var delegate: TableViewCellDelegate?
    
    var ncgContent: NCGContent? {
        didSet {
            if let ncgContent = ncgContent {
                contentNameLabel.text = ncgContent.contentName
                contentDescription.text = ncgContent.url
            } else {
                contentNameLabel.text = ""
                contentDescription.text = ""
            }
        }
    }
    
    @IBAction func pauseOrResumeTapped(_ sender: AnyObject) {
        if(pauseButton.titleLabel!.text == "Pause") {
            delegate?.pauseTapped(self)
        } else {
            delegate?.resumeTapped(self)
        }
    }
    
    @IBAction func cancelTapped(_ sender: AnyObject) {
        delegate?.cancelTapped(self)
    }
    
    @IBAction func downloadTapped(_ sender: AnyObject) {
        if Recharbility.isConnectedToNetwork() {
            delegate?.downloadTapped(self)
        } else {
            let alertController = UIAlertController(title: "Download Failed", message: "network connect failed", preferredStyle: .alert)
            
            let okAction = UIAlertAction(title: "확인", style: UIAlertActionStyle.destructive){ (action: UIAlertAction) in
                print("download - network connect failed")
            }
            alertController.addAction(okAction)
            UIApplication.shared.keyWindow?.rootViewController?.present(alertController, animated: true, completion: nil)
        }
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    func setNCGCell(ncgContent: NCGContent, indexPath: IndexPath, downloaded: Bool, download: NCGDownload?) {
        contentNameLabel.text = ncgContent.contentName
        contentDescription.text = ncgContent.url
        
        var showControls = false
        if let download = download {
            showControls = true
            let title = download.isDownloading ? "Pause" : "Resume"
            pauseButton.setTitle(title, for: .normal)
            progressLabel.text = download.isDownloading ? "Downloading..." : "Paused"
        }
        
        if indexPath.section == 1 {
            pauseButton.isHidden = !showControls
            cancelButton.isHidden = !showControls
            progressView.isHidden = !showControls
            progressLabel.isHidden = !showControls
            
            selectionStyle = downloaded ? UITableViewCellSelectionStyle.gray : UITableViewCellSelectionStyle.none
            downloadButton.isHidden = downloaded || showControls
        }
    }
    
    func updateDisplay(progress: Float, totalSize : String) {
        progressView.progress = progress
        progressLabel.text = String(format: "%.1f%% of %@", progress * 100, totalSize)
    }

}
