//
//  NCGPallyConSDKManager.swift
//  SDKSample-Swift
//
//  Created by INKA Entworks.
//  Copyright © 2018년 PallyCon. All rights reserved.
//

import UIKit
import AVKit

class NCGPallyConSDKManager: NSObject {
    
    static let sharedManager = NCGPallyConSDKManager()
    
    // SDK Callback
    var httpStatusCode: Int32?
    var httpStatusMessage: String?
    var httpStatusLastMessage: String?
    var httpHeader: Dictionary<String, Any>?
    
    var pallyconNCGSDK: Ncg2Agent? {
        return (Ncg2Agent.sharedInstance() as? Ncg2Agent)
    }
    
    func initialize() -> Bool {
        do {
            pallyconNCGSDK?.setExceptionalEventDelegate(self)
            
            // The initialize() function should be called only once. Otherwise, a memory leak will occur.
            if (try pallyconNCGSDK?.initialize(OfflineSupportYes, rodbPath: nil, deviceId: nil)) != nil {
                //
                // HTTP Request Callback(optional)
                //
                //pallyconNCGSDK?.setHttpRequestDelegate(self)
                //pallyconNCGSDK?.disableLog()
                return true
            }
            return false
        } catch {
            print("Error : \(error)")
        }
        return false
    }
    
    //
    //  Local web server message
    //
    func setWebServerDelegate(delegate:WebServerDelegate) {
        pallyconNCGSDK?.getLocalWebServerInstance().setWebServerDelegate(delegate)
    }
    
    //
    // Check the license information for external output.
    // True: Allow external output
    // False : No external output
    //
    func isContentAllowExternalDisplay(ncgContent: NCGContent) -> Bool {
        let licenseInfo: Ncg2LicenseInformation?
        licenseInfo = self.contentLicenseInfo(ncgContent:ncgContent)
        if licenseInfo?.getOutputProtectionPermission().getIsExternalDisplayAllow() == true {
            return true
        }
        return false
    }
    
    //
    // Returns the license information of the content from the DB.
    // If the DB does not have a license, ask the license server.
    //
    func contentLicenseInfo(ncgContent: NCGContent) -> Ncg2LicenseInformation? {
        do {
            var lv: LicenseValidation = LicenseValidation.init(1)
            var li: Ncg2LicenseInformation?
            let ncgUrl: String?
            if ncgContent.downloaded {
                ncgUrl = ncgContent.localPath
            } else {
                ncgUrl = ncgContent.url
            }
            
            try pallyconNCGSDK?.getLicenseInfo(byPath: ncgUrl, licenseValidation: &lv, licenseInformation: &li)
            if lv == LicenseValidationNotExist {
                if self.acquireLicense(ncgContent: ncgContent) {
                    li = self.contentLicenseInfo(ncgContent: ncgContent)!
                }
            }
            return li
        } catch {
            print("Error : \(error)")
        }
        return nil
    }
    
    //
    // Verify that it is NCG content.
    //
    func isNcgContent(ncgContent: NCGContent) -> Bool {
        do {
            if ncgContent.downloaded {
                return ((try pallyconNCGSDK?.isNcgContent(ncgContent.localPath)) != nil)
            } else {
                return ((try pallyconNCGSDK?.isNcgContent(ncgContent.url)) != nil)
            }
        } catch {
            print("Error : \(error)")
        }
        return false
    }
    
    //
    // Verify that the license for the content is valid.
    //
    func licenseCheck(ncgContent: NCGContent) -> Bool {
        do {
            var licenseValidation: LicenseValidation = LicenseValidation.init(1)
            let ncgUrl: String?
            if ncgContent.downloaded {
                ncgUrl = ncgContent.localPath
            } else {
                ncgUrl = ncgContent.url
            }

            if ((try pallyconNCGSDK?.checkLicenseValid(byPath: ncgUrl, result: &licenseValidation)) != nil) {
                if licenseValidation == LicenseValidationValid {
                    return true
                } else {
                    switch (licenseValidation){
                    case LicenseValidationAbnormalDevice: print("Detected Jailbreak Device"); break
                    case LicenseValidationBeforeStartDate: print("Before Start Date"); break
                    case LicenseValidationDetectedDeviceTimeModified: print("Detected Device Time Modified"); break
                    case LicenseValidationExceededPlayCount: print("Exceeded Play Count"); break
                    case LicenseValidationExpired: print("Expired Date"); break
                    case LicenseValidationNotExist: print("License Not Exist");
                    if self.acquireLicense(ncgContent: ncgContent, token: ncgContent.token) {
                            return self.licenseCheck(ncgContent: ncgContent)
                        }
                        break
                    case LicenseValidationNotSupportOffline: print("Not Suppoert Offline"); break
                    case LicenseValidationOfflineTooLong: print("It was offline for a Long Time. Connect the Internet");break
                    case LicenseValidationScreenRecorderDetected: print("Detected Screen Recorder"); break
                    case LicenseValidationValid: print("Have a valid license"); break
                        default: break
                    }
                    
                    return false
                }
            }
        } catch {
            print("Error : \(error)")
        }
        return false
    }
    
    //
    // If the DB does not have a license, request a license.
    // You can decide whether to save licenses to the DB(isTemporary).
    //
    func acquireLicense(ncgContent:NCGContent, token: String = "" ) -> Bool {
        
        var isTemporary: Bool = false
        
        if ncgContent.url.hasPrefix("http://") || ncgContent.url.hasPrefix("https://") {
            if !ncgContent.downloaded {
                isTemporary = true
            }
        }
        
        do {
            if ncgContent.downloaded {
                if ncgContent.token.isEmpty {
                    return ((((try pallyconNCGSDK?.acquireLicense(byPath: ncgContent.url, userID: "utest", orderID: "", isTemporary: isTemporary)) != nil)))
                } else {
                    return ((((try pallyconNCGSDK?.acquireLicense(byToken: ncgContent.token, isTemporary: isTemporary)) != nil)))
                }
            } else {
                if ncgContent.token.isEmpty {
                    return ((((try pallyconNCGSDK?.acquireLicense(byPath: ncgContent.url, userID: "utest", orderID: "", isTemporary: isTemporary)) != nil)))
                } else {
                    return ((try pallyconNCGSDK?.acquireLicense(byToken: ncgContent.token, isTemporary: isTemporary)) != nil)
                }
            }
        } catch {
            print("Error : \(error)")
            return false
        }
    }
    
    //
    // NCG content delivers decoded data via a local web server.
    // You must play it as a local web server address when playing.
    //
    func getPlaybackUrl(ncgContent:NCGContent, remoteNcgFilePath: String, fileSize: Int64) -> AVURLAsset? {
        do {
            var localUrl:String
            if pallyconNCGSDK?.getLocalWebServerInstance().isServerAlive() == false {
                try pallyconNCGSDK?.getLocalWebServerInstance().start()
            }
            if ncgContent.downloaded {
                // Downloaded Content
                try localUrl = (pallyconNCGSDK?.getLocalWebServerInstance().addLocalFilePath(forPlayback: ncgContent.localPath,
                                                                                             remoteUrlForDnp: nil,
                                                                                             fileSize: 0))!
            } else if ncgContent.url.hasSuffix("m3u8") || ncgContent.url.hasSuffix("smil") {
                // HLS Content
                if ncgContent.live {
                    try localUrl = (pallyconNCGSDK?.getLocalWebServerInstance().addHttpLiveStreamUrl(forPlayback: ncgContent.url, isLiveHLS: true))!
                } else {
                    try localUrl = (pallyconNCGSDK?.getLocalWebServerInstance().addHttpLiveStreamUrl(forPlayback: ncgContent.url, isLiveHLS: false))!
                }
                //try localUrl = (pallyconNCGSDK?.getLocalWebServerInstance()?.addHttpLiveStreamUrl(forPlayback: ncgContent.url))!
            } else if ncgContent.url.hasPrefix("http") {
                // Progressive Download Content
                try localUrl = (pallyconNCGSDK?.getLocalWebServerInstance().addProgressiveDownloadUrl(forPlayback: ncgContent.url))!
            } else {
                // Downloading And Play
                try localUrl = (pallyconNCGSDK?.getLocalWebServerInstance().addLocalFilePath(forPlayback: ncgContent.url,
                                                                                             remoteUrlForDnp: remoteNcgFilePath,
                                                                                             fileSize: fileSize))!
            }
            print("NCG Playback URL : \(localUrl)")
            return AVURLAsset(url: URL(string: localUrl)!)
        } catch {
            print("Error : \(error)")
            return nil
        }
    }
    
    //
    // Remove playback information after playback is completed or before playback through the local web server.
    //
    func clearPlaybackUrl() {
        pallyconNCGSDK?.getLocalWebServerInstance().clearVirtualPlaybackUrls()
    }
    
    func removeLicense(ncgContent: NCGContent) {
        do {
            if ncgContent.downloaded {
                try pallyconNCGSDK?.removeLicense(byPath: ncgContent.localPath)
            } else {
                try pallyconNCGSDK?.removeLicense(byPath: ncgContent.url)
            }
        } catch {
            print("\(error)")
        }
    }
    
    //
    // SDK has time information that is managed internally.
    // If the content is valid but has expired, call secureTimeUpdate().
    // The device must be connected to the Internet at the time of call.
    //
    func secureTimeUpdate() {
        do {
            try pallyconNCGSDK?.updateSecureTimeFromServer()
        } catch {
            print("Error : \(error)")
        }
    }
}

extension NCGPallyConSDKManager: NcgExceptionalEventDelegate {
    func logHandle(_ error: Error!) {
        print("logHandle [\(error.localizedDescription)]")
    }
    
    func log(_ logMessage: String!) {
        print("log [\(logMessage!)]")
    }
}


extension NCGPallyConSDKManager: NcgHttpRequestDelegate {
    
    func handleHttpRequest(_ requestURL: String!, urlParameter parameter: String!, requestHeaders header: [AnyHashable : Any]!) -> Data! {
        
        var httpUrl: String?
        httpUrl = requestURL.replacingOccurrences(of: " ", with: "")
        if parameter.count > 0 {
            httpUrl = httpUrl! + "?" + parameter
        }
        print("[handleHttpRequest] parameter ----------- \n \(String(describing: parameter)) \n")
        print("[handleHttpRequest] http + parameter ---- \n \(String(describing: httpUrl)) \n")

        var request = URLRequest(url: URL(string: httpUrl!)!)
        let semaphore = DispatchSemaphore(value: 0)
        
        request.httpMethod = "GET"
        
        if let requestHeader = header as? [String : String] {
            requestHeader.forEach { (arg0) in
                let (key, value) = arg0
                request.setValue(value, forHTTPHeaderField: key)
                print("Request Header = \(key): \(value)")
            }
        }

        var resultData: Data?
        
        let session = URLSession.shared
        let task = session.dataTask(with: request, completionHandler: {(data, response, error) in
            resultData = data!
            if let res = response as? HTTPURLResponse {
                res.allHeaderFields.forEach { (arg0) in
                   let (key, value) = arg0
                       print("\(key): \(value)")
                   }
                self.httpHeader = res.allHeaderFields as? [String : String]
            }
            semaphore.signal()
        })

        task.resume()
        semaphore.wait()
        
        return resultData
    }
    
    func getResponseStatus() -> Int32 {
        return httpStatusCode!
    }
    
    func getResponseMessage() -> String! {
        return httpStatusMessage
    }
    
    func getLastErrorMessage() -> String! {
        return httpStatusLastMessage
    }
    
    func getResponseHttpHeader() -> [AnyHashable : Any]! {
        return httpHeader
    }
}
