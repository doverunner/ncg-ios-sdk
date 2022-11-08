//
//  NCGContentManager.swift
//  PallyCon.Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import UIKit
import AVFoundation
import AVKit

class NCGContentManager: NSObject {
    
    static let sharedManager = NCGContentManager()
    
    private var hlsContents = [NCGContent]()
    private var mp4Contents = [NCGContent]()
    fileprivate let baseDownloadURL: URL
    
    // Get local file path: download task stores tune here; AV player plays it.
    let documentsPath = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask).first!
    func localFilePath(for url: URL) -> URL {
        return documentsPath.appendingPathComponent(url.lastPathComponent)
    }
    
    override private init() {
        baseDownloadURL = URL(fileURLWithPath: NSHomeDirectory())
        
        super.init()
        
        guard let contentsFilepPath = Bundle.main.path(forResource: "Contents", ofType: "plist") else { return }
        
        // Create an array from the contents of the Streams.plist file.
        guard let arrayOfContents = NSArray(contentsOfFile: contentsFilepPath) as? [[String: AnyObject]] else { return }
        
        var indexMP4 = 0
        for entry in arrayOfContents {
            // Get the Stream name from the dictionary
            guard let contentName = entry[NCGContent.Item.name] as? String,
                let contentPlaylistURLString = entry[NCGContent.Item.url] as? String else { continue }
            
            let optionalId = (entry[NCGContent.Item.optionalId] as? String) ?? ""
            let token = (entry[NCGContent.Item.token] as? String) ?? ""
            let licenseAcquireUrl = (entry[NCGContent.Item.licenseAcquireUrl] as? String) ?? ""
            
            var ncgContent: NCGContent!
            guard let contentPlaylistURL = URL(string: contentPlaylistURLString) else {
                continue
            }
            
            let urlAsset = AVURLAsset(url: contentPlaylistURL)
            ncgContent = NCGContent(licenseAcquireUrl: licenseAcquireUrl, optionalId: optionalId, token: token,
                                    urlAsset: urlAsset, url: contentPlaylistURLString, contentName: contentName)
            
            let downloadedPath = localFilePath(for: contentPlaylistURL)
            let fileManager = FileManager.default
            
            if fileManager.fileExists(atPath: downloadedPath.path) {
                ncgContent.localPath = downloadedPath.path
                ncgContent.downloaded = true
            }

            if let isHLS = entry[NCGContent.Item.isHLS] as? Bool, isHLS {
                if let isLive = entry[NCGContent.Item.isLive] as? Bool, isLive {
                    ncgContent.live = true;
                    self.hlsContents.append(ncgContent)
                } else {
                    self.hlsContents.append(ncgContent)
                }
            } else {
                ncgContent.index = indexMP4
                self.mp4Contents.append(ncgContent)
                indexMP4 += 1
            }
        }
    }
    
    func numberOfContent(section: Int) -> Int {
        if section == 0 {
            return self.hlsContents.count
        } else {
            return self.mp4Contents.count
        }
    }
    
    func ncgContent(indexPath: IndexPath) -> NCGContent {
        if indexPath.section == 0 {
            return self.hlsContents[indexPath.row]
        } else {
            return self.mp4Contents[indexPath.row]
        }
    }
    
    func setNcgContent(ncgContent: NCGContent, downloaded: Bool) {
        if downloaded {
            self.mp4Contents[ncgContent.index] = ncgContent
        } else {
            var saveNcgContent = ncgContent
            saveNcgContent.downloaded = false
            saveNcgContent.localPath = String.init()
            self.mp4Contents[ncgContent.index] = saveNcgContent
        }
    }
    
    func setContentUrlAsset(for section: Int, index: Int, urlAsset: AVURLAsset) {
        if section == 0 {
            self.hlsContents[index].urlAsset = urlAsset
        } else {
            self.mp4Contents[index].urlAsset = urlAsset
        }
    }
}
