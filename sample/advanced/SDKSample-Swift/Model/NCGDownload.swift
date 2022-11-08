//
//  NCGDownload.swift
//  SDKSample-Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import Foundation

class NCGDownload {
    var ncgContent: NCGContent
    
    init(ncgContent: NCGContent) {
        self.ncgContent = ncgContent
    }
    
    var task: URLSessionDownloadTask?
    var isDownloading: Bool = false
    var resumeData: Data?
    var progress: Float = 0
}
