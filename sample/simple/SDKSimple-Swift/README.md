

# PallyCon NCG SDK Sample 

This sample demonstrates how to use the `iOSNcgSDK` framework to play .mp4(NCG content) or HTTP Live Streams(HLS-AES) hosted on remote servers as `Swift` language.



## Using the Sample

- Build and run the sample on an actual device running iOS 11.0 or later using Xcode.

- With `iOSNcgSDK` framework, you can know about NCG(MP4) content streaming playback.

  > Note: Encrypted HLS content is not supported for playback on the simulator. 



### Adding `iOSNcgSDK.framework` to the Sample

- Add `iOSNcgSDK.framework` to Xcode project target in `General` -> `Linked Frameworks and Librarys`.
- Add `iOSNcgSDK.framework` to the `Build Settings` -> `Search Paths` -> `Framework Search Paths` path.
- Import the SDK header to `Bridging Header` file.

~~~objectivec
  // Bridging Header file : SDKSimple-Swift-Bridging-Header.h
  #import <iOSNcgSDK/iOSNcgSDK.h>
~~~



### Adding Streams to the Sample

- Prepare to acquire the license by entering the NCG content URL and Token in the `ViewController.swift` file.

~~~swift
  // ViewController.swift
  let ContentURL = "Content URL"
  let Token = "Token String"
~~~



### Application Transport Security

- If any of the streams you add are not hosted securely, you will need to add an Application Transport Security(ATS) exception in the Info.plist.
- More information on ATS and the relevant plist keys can be found in the following article:
- Information Property List Key Reference - NSAppTransportSecurity: <https://developer.apple.com/library/ios/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW33>



## Main Files

__ViewController.swift__ 

- Examples of NCG SDK initialization and content (MP4) license acquisition and playback are implemented.



## PallyCon Multi-DRM Service

PallyCon Multi-DRM Service description and inquiries are available at the address below.
- [PallyCon Homepage](https://www.pallycon.com)
- [PallyCon Multi-DRM Document](https://pallycon.com/docs/)


---



# PallyCon NCG SDK 샘플

이 샘플은 `iOSNcgSDK`프레임워크를 사용하여 원격 서버에서 호스팅되는 .mp4 (NCG 컨텐츠) 또는 HTTP 실시간 스트림 (HLS-AES)을 `swift` 언어로 구현하여 재생하는 방법을 보여줍니다.



## Using the Sample

- Xcode를 사용하여 iOS 11.0 이상의 실제 디바이스에서 샘플을 빌드와 실행하십시오.

- `iOSNcgSDK` 프레임워크으로 NCG(MP4) 콘텐츠 스트리밍 재생에 대해 알 수 있습니다. 

  > Note: 암호화된 HLS 콘텐츠는 시뮬레이터에서 재생을 지원하지 않습니다.



### Adding `iOSNcgSDK.framework` to the Sample

- Xcode 프로젝트 타겟에 `General` -> `Embedded Binaries`에 `iOSNcgSDK.framework`을 추가합니다.
- 추가한 `iOSNcgSDK.framework` 경로를 `Build Settings` -> `Search Paths` -> `Framework Search Paths`에 입력합니다.
- `Bridging Header`를 추가하고 SDK 헤더를 `import` 합니다.

	~~~objectivec
		// Bridging Header file : SDKSimple-Swift-Bridging-Header.h
		#import <iOSNcgSDK/iOSNcgSDK.h>
	~~~



### Adding Streams to the Sample

- ViewController.swift 파일에 NCG 콘텐츠 URL과 Token을 입력하여 라이선스를 획득 준비를 합니다.

~~~swift
  // ViewController.swift
  let ContentURL = "Content URL"
  let Token = "Token String"
~~~



### Application Transport Security

- HLS 스트리밍이 스트리밍되지 않는다면 Application Transport Security (ATS) 예외를 Info.plist에 추가해야 합니다. ATS 와 plist 키에 대한 설명은 다음 문서에서 확인 할 수 있습니다.  
- Information Property List Key Reference - NSAppTransportSecurity: <https://developer.apple.com/library/ios/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW33>



## Main Files

__ViewController.swift__ 

- NCG SDK 초기화와 콘텐츠(MP4)라이선스 획득과 재생 관련 예제가 구현되어 있습니다.





## PallyCon 멀티 DRM 서비스

PallyCon 멀티 DRM 서비스 설명과 문의 사항은 아래 주소로 제공됩니다.
- [PallyCon Homepage](https://www.pallycon.com)
- [PallyCon Multi-DRM Document](https://pallycon.com/docs/)


Copyright (C) 2019 INKA Entworks. All rights reserved.

