//
//  TableViewController+URLSessionDelegates.swift
//  SDKSample-Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import Foundation
import UIKit

extension TableViewController: URLSessionDownloadDelegate {
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didFinishDownloadingTo location: URL) {
        guard let sourceURL = downloadTask.originalRequest?.url else { return }
        let download = downloadService.activeDownloads[sourceURL]
        downloadService.activeDownloads[sourceURL] = nil

        let destinationURL = localFilePath(for: sourceURL)
        print("destinationURL: \(destinationURL)")

        let fileManager = FileManager.default
        try? fileManager.removeItem(at: destinationURL)
        do {
            try fileManager.copyItem(at: location, to: destinationURL)
            download?.ncgContent.downloaded = true
        } catch let error {
            print("Could not copy file to disk: \(error.localizedDescription)")
        }

        DispatchQueue.main.async {
            let strPath: String
            var isNcg: Bool = false
            if destinationURL.absoluteString.hasSuffix(".ncg") {
                strPath = destinationURL.path
                isNcg = true
            } else {
                strPath = destinationURL.absoluteString
            }
            download?.ncgContent.localPath = strPath
            NCGContentManager.sharedManager.setNcgContent(ncgContent: (download?.ncgContent)!, downloaded: true )
            self.tableView.reloadData()
            
            if isNcg {
                // It is advisable to obtain a license after the content download is completed.
                if NCGPallyConSDKManager.sharedManager.acquireLicense(ncgContent: (download?.ncgContent)!) {
                    print("License Acquisition!!")
                }
            }
        }
    }
   
    func urlSession(_ session: URLSession, downloadTask: URLSessionDownloadTask, didWriteData bytesWritten: Int64, totalBytesWritten: Int64, totalBytesExpectedToWrite: Int64) {
        guard let url = downloadTask.originalRequest?.url,
            let download = downloadService.activeDownloads[url] else {
                return
        }
        
        download.progress = Float(totalBytesWritten) / Float(totalBytesExpectedToWrite)
        
        let totalSize = ByteCountFormatter.string(fromByteCount: totalBytesExpectedToWrite, countStyle: .file)
        DispatchQueue.main.async {
            if let tableViewCell = self.tableView.cellForRow(at: IndexPath(row: download.ncgContent.index, section: 1)) as? TableViewCell {
                tableViewCell.updateDisplay(progress: download.progress, totalSize: totalSize)
            }
        }
    }
}

// MARK: - URLSessionDeleagte
extension TableViewController: URLSessionDelegate {
    // Standard background session handler
    func urlSessionDidFinishEvents(forBackgroundURLSession session: URLSession) {
        DispatchQueue.main.async {
            if let appDelegate = UIApplication.shared.delegate as? AppDelegate,
                let completionHandler = appDelegate.backgroundSessionCompletionHandler {
                appDelegate.backgroundSessionCompletionHandler = nil
                completionHandler()
            }
        }
    }
}
