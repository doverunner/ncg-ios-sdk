//
//  NCGDownloadManager.swift
//  SDKSample-Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import Foundation

class NCGDownloadManager: NSObject {
    
    var downloadsSession: URLSession!
    var activeDownloads: [URL: NCGDownload] = [:]
    
    override init() {
        super.init()
    }
   
    func statDownload(_ ncgContent:NCGContent) {

        let download = NCGDownload(ncgContent: ncgContent)
        download.task = downloadsSession.downloadTask(with: URL(string: ncgContent.url)!)
        download.task!.resume()
        download.isDownloading = true
        activeDownloads[URL(string: download.ncgContent.url)!] = download
    }
    
    func pauseDownload(_ ncgContent:NCGContent) {
        guard let download = activeDownloads[URL(string: ncgContent.url)!] else { return }
        if download.isDownloading {
            download.task?.cancel(byProducingResumeData: { data in
                download.resumeData = data
            })
            download.isDownloading = false
        }
    }
    
    func cancelDownload(_ ncgContent:NCGContent) {
        if let download = activeDownloads[URL(string: ncgContent.url)!] {
            download.task?.cancel()
            activeDownloads[URL(string: ncgContent.url)!] = nil
        }
    }
    
    func resumeDownload(_ ncgContent:NCGContent) {
        guard let download = activeDownloads[URL(string: ncgContent.url)!] else { return }
        if let resumeData = download.resumeData {
            download.task = downloadsSession.downloadTask(withResumeData: resumeData)
        } else {
            download.task = downloadsSession.downloadTask(with: URL(string: download.ncgContent.url)!)
        }
        download.task!.resume()
        download.isDownloading = true
    }
}
