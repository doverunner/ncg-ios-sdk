//
//  NCGContent.swift
//  PallyCon.Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import AVFoundation

//
// NCG Content Struct
//
struct NCGContent {
    var contentId: String
    var optionalId: String
    var token: String
    var urlAsset: AVURLAsset
    var url: String
    var licenseAcquireUrl: String
    var localPath: String
    var contentName: String
    var downloaded: Bool = false
    var live: Bool = false
    var index: Int
    
    init(licenseAcquireUrl: String, optionalId: String, token: String, urlAsset: AVURLAsset, url: String, contentName: String) {
        self.licenseAcquireUrl = licenseAcquireUrl
        self.contentId = String.init()
        self.contentName = contentName
        self.optionalId = optionalId
        self.token = token
        self.urlAsset = urlAsset
        self.url = url
        self.localPath = String.init()
        self.downloaded = false
        self.live = false
        self.index = 0
    }
}

//
// Content license information
//
extension NCGContent {
    struct license {
        var acquireURL: String
        var totalCount: u_long
        var remainCount: u_long
        var startDate: String
        var endDate: String
        var isExternalDisplay: Bool
        var isJailBrokenAllow: Bool
    }
}


extension NCGContent {
    enum DownloadState: String {
        case notDownloaded
        case downloading
        case downloaded
        case pause
    }
}

extension NCGContent {
    struct Item {
        static let isHLS = "IsHLS"
        static let isLive = "IsLive"
        static let optionalId = "OptionalId"
        static let token = "Token"
        static let name = "ContentName"
        static let url = "ContentURL"
        static let licenseAcquireUrl = "LicenseAcquireURL"
    }
}
