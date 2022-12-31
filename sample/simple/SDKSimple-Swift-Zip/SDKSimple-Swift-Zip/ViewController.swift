//
//  ViewController.swift
//  SDKSimple-Swift-Zip
//
//  Created by yhpark on 2022/11/25.
//

import UIKit
import iOSNcgSDK

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        let zipPath = Bundle.main.path(forResource: "zipNcgLorem.zip", ofType: "ncg")
        
        do {
            // 1. NCG SDK initialize
            try (Ncg2Agent.sharedInstance() as! Ncg2Agent).initialize(OfflineSupportYes, rodbPath: nil, deviceId: nil)
            // 2. License Acquire
            try (Ncg2Agent.sharedInstance() as! Ncg2Agent).acquireLicense(byPath: zipPath, userID: "utest", orderID: "", isTemporary: false)
            
            // 3. Ncg Zip instance
            let zipfile = try (Ncg2Agent.sharedInstance() as! Ncg2Agent).createNcgFileZip()
            // 4. Zip Prepare
            try zipfile.ncgZipPrepare(zipPath!)
            
            let zipEntries = zipfile.ncgZipGetEntries()
            print("zip Entry count : \(zipEntries.count)")
            for entry in zipEntries {
                print("Entry Name : \(entry)");
            }
            
            // 5. Open the file to be used in the entry list.
            try zipfile.ncgZipOpenEntry("c.txt")
            
            // read buffer.
            let count = 1024*1024
            var buffer:[CChar] = [CChar](repeating: 0, count: count)
            // 6. Entry Read
            let readSize = zipfile.ncgZipRead(&buffer, bufferSize: Int32(count))
            print("read size \(readSize)")
            print("Buffer :: \(String(cString: buffer))")
            
            // 7. Zip close.
            zipfile.ncgZipClose()
            
        } catch {
            print(error.localizedDescription)
            return
        }
    }


}

