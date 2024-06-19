//
//  ContentView.swift
//  SDKSimple-SwiftUI
//
//  Created by yhpark on 2023/05/15.
//

import SwiftUI
import AVKit
import iOSNcgSDK

let ContentURL = "https://contents.pallycon.com/TEST/PACKAGED_CONTENT/TEST_SIMPLE/sintel-trailer.mp4.ncg"
let Token = "eyJrZXlfcm90YXRpb24iOmZhbHNlLCJyZXNwb25zZV9mb3JtYXQiOiJvcmlnaW5hbCIsInVzZXJfaWQiOiJ1dGVzdCIsImRybV90eXBlIjoibmNnIiwic2l0ZV9pZCI6IkRFTU8iLCJoYXNoIjoiK2prMVpOUUNNY0JRM2d3ZDl6UHNmZjh1eXJ4M2M3XC9CZUwxYmlYUTBDMHM9IiwiY2lkIjoiVGVzdFJ1bm5lciIsInBvbGljeSI6IjlXcUlXa2RocHhWR0s4UFNJWWNuSnNjdnVBOXN4Z3ViTHNkK2FqdVwvYm9tUVpQYnFJK3hhZVlmUW9jY2t2dUVmdUx0dlVMWXEwTnVoNVJaOFhGYzQ1RWxHd1dcLzY3WVhUcTJQSDJ4Z3dIR1hDalVuaUgzbDQ4NVNmcDZjbmV1bm5qdjMxeGt5VHd6VlAzdVhIUGJWNWR3PT0iLCJ0aW1lc3RhbXAiOiIyMDIwLTExLTE4VDA1OjU2OjEzWiJ9";

struct ContentView: View {
    var body: some View {
        GeometryReader { geo in
            ZStack {
                player().frame(height: UIDevice.current.orientation.isLandscape ? geo.size.height:geo.size.height , alignment: .center)
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
 
struct player : UIViewControllerRepresentable {
    func makeUIViewController(context: UIViewControllerRepresentableContext<player>) -> AVPlayerViewController {

        let playerViewController = AVPlayerViewController()
        do {
            // 1. NCG SDK initialize
            try (Ncg2Agent.sharedInstance() as! Ncg2Agent).initialize(OfflineSupportYes, rodbPath: nil, deviceId: nil)
            // 2. License Acquire
            try (Ncg2Agent.sharedInstance() as! Ncg2Agent).acquireLicense(byToken: Token, isTemporary: true)
            // 3. You must specify a delegate of the local Web server and implement the webServerDelegate protocol.
            (Ncg2Agent.sharedInstance() as! Ncg2Agent).getLocalWebServerInstance().setWebServerDelegate(NCGWebServer())
            // 4. Local web server start.
            try (Ncg2Agent.sharedInstance() as! Ncg2Agent).getLocalWebServerInstance().start()
            // 5. Acquire the local Web server address to be played back.
            let playUrl = try (Ncg2Agent.sharedInstance() as! Ncg2Agent).getLocalWebServerInstance().addProgressiveDownloadUrl(forPlayback: ContentURL)
            // 6. Playback
            let player = AVPlayer(url: URL(string: playUrl)!)
            playerViewController.player = player
            player.play()
            return playerViewController

        } catch {
            print("\(error)")
        }
        return playerViewController
    }
     
    func updateUIViewController(_ uiViewController: AVPlayerViewController, context: UIViewControllerRepresentableContext<player>)  {
        
    }
}

class NCGWebServer: NSObject, WebServerDelegate {
    func onNotification(_ notificationCode: Int32, notifyMessage: String!) {
        print("\(notificationCode):\(String(describing: notifyMessage))")
    }
    func onError(_ errorCode: Int32, errorMessage: String!) {
        print("\(errorCode):\(String(describing: errorMessage))")
    }
    func onCheckPlayerStatus(_ uri: String!) -> PlayerState {
        // if you have not been prepared you should return 'PlayerStateFail'
        // instead of 'PlayerStateReadyToPlay'
        return  PlayerStateReadyToPlay
    }
}

