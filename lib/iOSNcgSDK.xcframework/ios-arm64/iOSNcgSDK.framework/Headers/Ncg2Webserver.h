//
//  Ncg2Webserver.h
//  iOSNcgSDK
//
//  Created by inka on 2015. 2. 13..
//  Copyright (c) 2015년 inka. All rights reserved.
//

#import <Foundation/Foundation.h>

/// Interface to deliver event from local web server outside SDK
/// The method is called for the applicable interface to deliver an error or notice, or to confirm the status of Player.
/// A client using SDK must implement the applicable interface to register the object through the method of setWebServerDelegate:.
typedef enum _WebserverErrorCode
{
    /**
     * @if KOREA
     * LWS_NOTIFY_SUCCESS : 통지 코드.
     * 성공 통지에 대한 통지코드로써 예약된 값으로 현재 사용되고 있지 않음.
     * @endif
     *
     * @if ENGLISH
     * LWS_NOTIFY_SUCCESS: Notice code.
     * Notice code for success notice, which is a reserved value and currently not used.
     * @endif
     */
    LWS_NOTIFY_SUCCESS							= 1000,
    
    /**
     * @if KOREA
     * LWS_NOTIFY_NETWORK_ERROR : 통지 코드
     * 로컬웹서버내부에서 실제 컨텐츠가 존재하는 Remote 웹서버와 통신하는데 오류가 발생된 경우.
     * 해당 경우에 Player가 Retry 할 수 있도록 오류로 처리하지 않고 통지로 처리하게 된다.
     * 해당 통지를 받았을때 사용자에게 관련 정보를 보여줄 수 있거나 무시할 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_NOTIFY_NETWORK_ERROR: Notice code
     * In case that an error occurs connecting to Remote web server where the actual content exists inside the local web server.
     * In this case, in order for Player to Retry, it is processed not as an error but as a notice.
     * When receiving this notice, one can show relevant information to a user or ignore it.
     * @endif
     */
    LWS_NOTIFY_NETWORK_ERROR					= 1001,
    
    /**
     * @if KOREA
     * LWS_NOTIFY_DNP_READ_FAIL_PLAY_ERROR : 통지 코드
     * 다운로드를 받는 도중에 재생하는 경우(PD와는 다름), 재생속도가 다운로드 속도보다 빨라져서 Read를 시도해도 데이터를 못 읽는 경우가 발생될 수 있다.
     * Read 실패가 누적되어 더이상 진행이 불가능한 경우에 해당 통지코드가 발생된다.
     * 다운로드 받으면서 재생하는(DnP) 처리를 하지 않는 경우 해당 통지를 무시해도 된다.
     * 만약 DnP를 지원한다면 해당 통지코드를 인식해서 적절한 사용자 메시지를 보여줄 수 있다.
     * @endif
     *
     * @if ENLGISH
     * LWS_NOTIFY_DNP_READ_FAIL_PLAY_ERROR: Notice code
     * In case that playing while downloading (different from PD), due to the faster downloading speed than playing speed, the case may occur not to read data even when trying to read.
     * When it is not possible to progress any longer due to the accumulated failure of Read, this notice code creates.
     * In case of not processing play (DnP) while downloading, this notice may be ignored.
     * If DnP is supported, this notice code is recognized to show the applicable user message.
     * @endif
     */
    LWS_NOTIFY_DNP_READ_FAIL_PLAY_ERROR			= 1002,
    
    /**
     * @if KOREA
     * LWS_NOTIFY_HDMI_DETECTED : 통지 코드
     * HDMI 장치와 연결되어있는 상태이고 HDMI 출력을 지원하지 않는 라이선스로 셋팅된 컨텐츠를 재생시킨 경우이다.
     * 해당 오류통지를 통해 HDMI출력을 하용하지 않는 컨텐츠라는 적절한 사용자 메시지를 보여줄 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_NOTIFY_HDMI_DETECTED: Notice code
     * It is the case to play the contents connected to HDMI device and set with the license that does not support HDMI output.
     * This error notice may show the applicable user message specifying that it is the content not allowing HDMI output.
     * @endif
     */
    LWS_NOTIFY_HDMI_DETECTED 					= 1003,
    
    /**
     * @if KOREA
     * LWS_NOTIFY_DECRYPT_DISABLED : 통지 코드
     * 이 통지 코드는 플레이어가 Clear된 URL로 요청한 경우 통지된다.
     * @endif
     *
     * @if ENGLISH
     * LWS_NOTIFY_DECRYPT_DISABLED : Notice code
     * This notice code is notified when player requests the local web server with cleared url.
     * @endif
     */
    LWS_NOTIFY_DECRYPT_DISABLED					= 1004,
    
    /**
     * @if KOREA
     * LWS_ERROR_UNKNOWN_ERROR : 오류 코드
     * 로컬웹서버 동작시 복구가 불가능한 오류가 발생된 경우에 해당 오류통지를 받게된다.
     * 해당 오류코드가 발생되는 경우 로컬웹서버 구현상 오류인 경우이므로 SDK 제작사에 문의해야 한다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_UNKNOWN_ERROR: Error code
     * When an error occurs, which is impossibly recovered while local web server runs, this error notice is received.
     * This error code means the case of an error in implementing a local web server, please contact the applicable SDK manufacturer.
     * @endif
     */
    LWS_ERROR_UNKNOWN_ERROR						= 10000,
    
    /**
     * @if KOREA
     * LWS_ERROR_FILE_IO_ERROR : 오류 코드
     * 파일 I/O 관련 동작이 실패된 경우에 해당 오류코드로 통지를 받게 된다.
     * 해당 오류가 발생된다면 권한문제를 체크해보고 권한에 문제가 없는데 문제가 발생되는 경우라면 에러메시지를 포함한 정보를 SDK 제작사 전달하여 문의해 볼 수 있다.
     * 즉, 일반적인 시나리오에서 발생되는 오류상황은 아니다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_FILE_IO_ERROR: Error code
     * When an act related to file I/O fails, this error code is notified.
     * When this error occurs, check authorization matter; and if no problem in authorization but there is a trouble, you may convert the information including the error message to the applicable SDK manufacturer for inquiry.
     * i.e., it is not an error situation that can occur in an ordinary scenario.
     * @endif
     */
    LWS_ERROR_FILE_IO_ERROR 					= 10002,
    
    /**
     * @if KOREA
     * LWS_ERROR_HLS_PROXY_SERVER_ERROR : 오류 코드
     * HLS 컨텐츠를 처리하다가 복구가 불가능한 오류가 발생된 경우이다.
     * 일반적인 시나리오에서 발생되는 오류상황이 아니며 해당 오류가 발생되는 경우 에러메시지를 포함한 정보를 SDK 제작사 전달하여 문의해 볼 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_HLS_PROXY_SERVER_ERROR : Error code
     * It is the case of an unrecoverable error occurring in processing HLS content.
     * This is not an error situation that can occur in an ordinary scenario; and you may convert the information including the error message to the applicable SDK manufacturer for inquiry.
     * @endif
     */
    LWS_ERROR_HLS_PROXY_SERVER_ERROR            = 10003,
    
    /**
     * @if KOREA
     * LWS_ERROR_SECURITY_THREAT_DETECTED : 오류 코드
     * 컨텐츠보안에 위협 되는 환경이 감지된 경우 해당 오류가 발생된다.
     * 재생 URL을 외부에서 접속한다던가 네트워크 패킷 스니핑등의 동작이 감지된 경우 오류가 발생된다.
     * 해당 오류통지를 통해 컨텐츠보안에 위협이되는 동작이 발생되었다는 적절한 사용자 메시지를 출력할 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_SECURITY_THREAT_DETECTED : Error code
     * When an environment threatening content security is detected, this error occurs.
     * When Play URL is externally accessed or an act such as network packet sniffing is detected, this error occurs.
     * Based on this error notice, you can print out the appropriate user message specifying that an act threatening content security is created.
     * @endif
     */
    LWS_ERROR_SECURITY_THREAT_DETECTED			= 10004,
    
    /**
     * @if KOREA
     * LWS_ERROR_INVALID_LICENSE_ERROR : 오류 코드
     * 라이선스가 유효하지 않은 컨텐츠를 재생하려고 시도한 경우 해당 오류코드가 통지될 수 있다.
     * 이 경우에는 개발단계에서 적절히 라이선스를 미리 획득하지 않고 재생을 시도한 경우이므로 재생전에 라이선스를 미리 확보하도록 앱 제작사에서 직접 수정주어서 문제를 해결해야 한다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_INVALID_LICENSE_ERROR : Error code
     * When the content with invalid license is tried to play, this error code may be notified.
     * In this case which tries to play without prior acquiring the applicable license in the stage of development, you should advise App manufacturer to prior acquire such license before playing in order to solve the problem.
     * @endif
     */
    LWS_ERROR_INVALID_LICENSE_ERROR 			= 10006,
    
    /**
     * @if KOREA
     * LWS_ERROR_UNSUPPORTED_OPERATION_ERROR : 오류 코드
     * 지원되지 않는 동작이 구동된 경우 해당 오류코드가 통지될 수 있다.
     * 해당 오류코드 통지된다면 에러메시지를 포함한 정보를 SDK 제작사 전달하여 문의해 볼 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_UNSUPPORTED_OPERATION_ERROR : Error code
     * If an act that is not supported is operated, this error code may be notified.
     * When this error code is notified, you can convert the information including error message to SDK manufacturer for inquiry.
     * @endif
     */
    LWS_ERROR_UNSUPPORTED_OPERATION_ERROR	 	= 10007,
    
    /**
     * @if KOREA
     * LWS_ERROR_INVALID_PARAMETER_ERROR : 오류 코드
     * 내부 구현상 잘못된 파라미터가 전달된 경우를 인식한 경우이다.
     * 해당 오류코드 통지된다면 에러메시지를 포함한 정보를 SDK 제작사 전달하여 문의해 볼 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_INVALID_PARAMETER_ERROR : Error code
     * This error code occurs when the cases where wrong parameters are converted in internal implementation are recognized.
     * When this error code is notified, you can convert the information including error message to SDK manufacturer for inquiry.
     * @endif
     */
    LWS_ERROR_INVALID_PARAMETER_ERROR			= 10008,
    
    /**
     * @if KOREA
     * LWS_ERROR_LOCAL_WEBSERVER_STOPED_ERROR : 오류 코드
     * 웹서버가 중지된 경우인데 플레이어와의 접속이 유지된 경우에 해당 오류코드가 통지될 수 있다.
     * 해당 오류코드 통지된다면 에러메시지를 포함한 정보를 SDK 제작사 전달하여 문의해 볼 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_LOCAL_WEBSERVER_STOPED_ERROR : Error code
     * If web server is stopped but still maintains the access to Player, this error code may be notified.
     * When this error code is notified, you can convert the information including error message to SDK manufacturer for inquiry.
     * @endif
     */
    LWS_ERROR_LOCAL_WEBSERVER_STOPED_ERROR      = 10009,
    
    /**
     * @if KOREA
     * LWS_ERROR_INVALID_PLAYER_ERROR : 오류 코드
     * 플레이어로부터 요청이 들어왔으나 onCheckPlayer() 에서 Fail을 반환한 경우 해당 오류코드가 통지된다.
     * 즉, 플레이어는 유효하지 않은 상태인제 URL 접속이 들어온 경우라면 보안상 문제로 볼 수 있으므로 사용자에게 보안경고를 띄울 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_INVALID_PLAYER_ERROR : Error code
     * If a request from Player is returned with Fail by onCheckPlayer(), this error code is notified.
     * In other words, when Player is not valid but URL access is received, which can be deemed as a security problem, security warning can be notified to a user.
     * @endif
     */
    LWS_ERROR_INVALID_PLAYER_ERROR              = 10010,
    
    /**
     * @if KOREA
     * LWS_ERROR_TRIAL_TIME_OUT : 오류 코드
     * Trial 버전에서만 해당 오류가 통지되 수 있다.
     * Trial 버전에서는 지정된 시간만큼만 재생되고 해당 오류통지 후 재생이 차단된다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_TRIAL_TIME_OUT : Error code
     * This error can be notified only in Trial version.
     * Trial version plays only for a designated time and then notifies this error before blocking the play.
     * @endif
     */
    LWS_ERROR_TRIAL_TIME_OUT 					= 10012,
    
    
    /**
     * @if KOREA
     * LWS_ERROR_HTTP_PROXY_INTERNAL_ERROR : 오류 코드
     * 해당 오류코드가 발생된다면 에러메시지를 포함한 정보를 SDK 제작사 전달하여 문의해 볼 수 있다.
     * @endif
     *
     * @if ENGLISH
     * LWS_ERROR_HTTP_PROXY_INTERNAL_ERROR : Error code
     * If this error code occurs, you can convert the information including the error message to SDK manufacturer for inquiry.
     * @endif
     */
    LWS_ERROR_HTTP_PROXY_INTERNAL_ERROR         = 10015
    
} WebserverErrorCode;

/// enum type to indicate Player status
/// Used in ``WebServerDelegate/onCheckPlayerStatus:`` method.
typedef enum _PlayerState
{
    /**
     * @if KOREA
     * 알 수 없는 플레이어의 상태
     * @endif
     *
     * @if ENGLISH
     * A status of unknown player
     * @endif
     */
    PlayerStateUnknown = 0x0020,
    
    /**
     * @if KOREA
     * 재생준비가 완료된 상태
     * @endif
     *
     * @if ENGLISH
     * A status ready to play
     * @endif
     */
    PlayerStateReadyToPlay = 0x0021,
    
    /**
     * @if KOREA
     * 에러 혹은 릴리즈된 상태
     * @endif
     *
     * @if ENGLISh
     * A status of error or release
     * @endif
     */
    PlayerStateFail = 0x0022
} PlayerState;

//---------------------------------------------------------------------------------
// @protocol WebServerDelegate
//---------------------------------------------------------------------------------

/// WebServerDelegate is local web server Delegate.
@protocol WebServerDelegate <NSObject>
@optional


/// When it is needed to notify from local web server outside SDK, the applicable method is called.
/// @param notificationCode Notice code
/// @param notifyMessage    Notice message
-(void) onNotification:(int)notificationCode  notifyMessage:(NSString*)notifyMessage;


/// When an error occurs while playing local web server, the applicable method is called.
/// @param errorCode Error code
/// @param errorMessage Error message
-(void) onError:(int)errorCode errorMessage:(NSString*)errorMessage;

/// This function is called while playing in order to continuously confirm whether a certain play URI is normally played in local web server.
/// @param uri URI to check the status of play
/// @return PlayerState return.
@required
-(PlayerState) onCheckPlayerStatus:(NSString*)uri;

@end

//---------------------------------------------------------------------------------
// @interface Ncg2Webserver
//---------------------------------------------------------------------------------

/// LocalWebServer class for play.
/// By using this class, you can acquire URL to set and play NCG files in local web server.
/// Play URL can be played with a general player.
/// Instance of the applicable interface can be obtained by ``Ncg2Agent/getLocalWebServerInstance``
@interface Ncg2Webserver : NSObject
@property (nonatomic, retain) NSString* httpCustomHeader;
@property (nonatomic, retain) id<WebServerDelegate> _WebServerDelegate;


/// ``Ncg2Webserver`` initialize.
/// However, instead of this function, you must create an instance with ``Ncg2Agent/getLocalWebServerInstance``.
/// @param ncgCoreH ncg core object.
/// @return ``Ncg2Webserver`` object.
-(id) init:(void*)ncgCoreH;


/// Local web server run.
/// @param error check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
-(BOOL) startWebserver:(NSError**)error;


/// local web server Stop.
-(void) stopWebserver;

/// The NCG file path is returned changed to the Local Web Server address.
/// @param path  NCG file path to play in a form of Local Playback
/// @param remoteUrlForDnp   remote URL
/// @param fileSize Playing NCG file in a form of DnP(DownlaodAndPlay) requires receiving the size of NCG file. If not in DnP play, set as 0.
/// @param error check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addLocalFilePathForPlayback:(NSString*)path remoteUrlForDnp:(NSString*)remoteUrlForDnp fileSize:(int64_t)fileSize error:(NSError**)error;


/// The NCG file path is returned changed to the Local Web Server address.
/// @param path NCG file path to play in a form of Local Playback.
/// @param remoteUrlForDnp remote URL.
/// @param contentId Content ID.
/// @param siteId Site ID.
/// @param fileSize file size.
/// @param error check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addLocalFilePathForPlayback:(NSString*)path remoteUrlForDnp:(NSString*)remoteUrlForDnp
                               contentId:(NSString*)contentId siteId:(NSString*)siteId
                                fileSize:(int64_t)fileSize error:(NSError**)error;


/// The NCG file path is returned changed to the Local Web Server address.
/// - Parameters:
///   - path: NCG file path.
///   - token: token
///   - error: check error if nil no. succeeded if nil.
/// - Returns: Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addLocalFileForUrl:(NSString*)path token:(NSString*)token error:(NSError**)error;

/// A method to set URL to play NCG in a form of ProgressiveDownload and acquire Play URL.
/// @param url URL path of NCG file to play in a form of ProgressiveDownload
/// @param error check error if nil no. succeeded if nil.
/// @param token token
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addProgressiveDownloadUrlFor:(NSString*)url token:(NSString*)token error:(NSError**)error;


/// The HLS-NCG URL is returned changed to the Local Web Server address.
/// - Parameters:
///    - url: HLS-NCG URL.
///    - token: token
///    - error: check error if nil no. succeeded if nil.
///
/// - Returns: Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addHttpLiveStreamForUrl:(NSString*)url token:(NSString*)token error:(NSError**)error;


/// A method to set URL to play NCG in a form of ProgressiveDownload and acquire Play URL.
/// @param url URL path of NCG file to play in a form of ProgressiveDownload
/// @param error check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addProgressiveDownloadUrlForPlayback:(NSString*)url error:(NSError**)error;


/// A method to set URL to play NCG in a form of ProgressiveDownload and acquire Play URL.
/// @param url URL path of NCG file to play in a form of ProgressiveDownload
/// @param contentId content id
/// @param siteId site id
/// @param error check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addProgressiveDownloadUrlForPlayback:(NSString*)url contentId:(NSString*)contentId siteId:(NSString*)siteId error:(NSError**)error;


/// A method to set HLS URL to play HLS content encrypted with NCG and acquire Play URL.
/// @param url       HLS content’s URL
/// @param error     check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addHttpLiveStreamUrlForPlayback:(NSString*)url error:(NSError**)error;


/// A method to set HLS URL to play HLS content encrypted with NCG and acquire Play URL.
/// If you are a HLS LIVE content, you must call this function.
/// @param url       HLS content’s URL
/// @param isLiveHLS YES for HLS LIVE Content
/// @param error     check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addHttpLiveStreamUrlForPlayback:(NSString*)url isLiveHLS:(BOOL)isLiveHLS error:(NSError**)error;


/// A method to set HLS URL to play HLS content encrypted with NCG and acquire Play URL
/// @param url       HLS content’s URL
/// @param contentId       Content ID of HLS content’s URL
/// @param error     check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addHttpLiveStreamUrlForPlayback:(NSString*)url contentId:(NSString*)contentId error:(NSError**)error;


/// A method to set HLS URL to play HLS content encrypted with NCG and acquire Play URL
/// If you are a HLS LIVE content, you must call this function.
/// @param url       HLS content’s URL
/// @param isLiveHLS YES for HLS LIVE Content
/// @param contentId    Content ID of HLS content’s URL
/// @param siteId site id
/// @param error     check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addHttpLiveStreamUrlForPlayback:(NSString*)url isLiveHLS:(BOOL)isLiveHLS contentId:(NSString*)contentId siteId:(NSString*)siteId error:(NSError**)error;


/// A method to set HLS URL to play HLS content encrypted with NCG and acquire Play URL.
/// Unlike addHttpLiveStreamUrlForPlayback(), this method does not prior check key file falling under m3u8 path.
/// @param url       HLS content’s URL
/// @param error     check error if nil no. succeeded if nil.
/// @return Local Web Server address.
/// > Important: URLs generated by the local web server are blocked from access after a period of time, so you should try to play them as soon as possible.
-(NSString*) addHttpLiveStreamUrlForPlaybackWithoutChecking:(NSString*)url error:(NSError**)error;


/// ``WebServerDelegate`` object can be registered to be informed of the events creating while playing local web server.
/// @param webServerDelegate ``WebServerDelegate`` object to receive events that can be created in local web server
-(void) setWebServerDelegate:(id<WebServerDelegate>)webServerDelegate;


/// Delete the set Play URL information.
-(void) clearVirtualPlaybackUrls;

///@TabNavigator {
///    @Tab("English") {
///        Activate or deactivate verification function for Cookie function.
///        When using MediaPlayer for Native provided by Android SDK, there are terminals which do not provide Cookie function; thus
///        setCookieChecking should be deactivated.
///        If it is played by Player where Cookie function is not provided, onError() callback method is called while playing.
///        If Player to play Play URL supports HTTP Cookie function, when the applicable Cookie function is activated, the level of security can be more improved.
///
///        @param enabled Set value for Cookie function.
///    }
///    @Tab("Korean") {
///        Cookie 기능에 대한 검증기능을 활성화 혹은 비활성화시킨다.
///        Android SDK에서 제공하는 Native용 MediaPlayer를 이용하는 경우 Cookie기능을 제공하지 않은 단말이 있으므로
///        setCookieChecking은 비활성화 되어야 한다.
///        만약 Cookie기능이 제공되지 Player에서 재생하게 된다면 재생 중 onError() 콜백메소드가 호출될 것이다.
///        재생 URL을 재생시킬 플레이어가 HTTP Cookie 기능을 지원한다면 해당 Cookie 기능을 활성화시킨다면 보안성을 더 높일 수 있다.
///
///        @param enabled Cookie기능에 대한 설정값.
///    }
///}
-(void) setCookieChecking:(BOOL)enabled;

-(BOOL) setHdmiDetection:(NSString*)path error:(NSError**)error;

-(BOOL) setHdmiDetectionByCID:(NSString*)cid siteID:(NSString*)siteID error:(NSError**)error;

//-(void) enableLog:(BOOL)enabled;

/// local web server running check.
/// @return running if YES. stop if NO.
-(BOOL) isServerAlive;

-(void) setCustomCookieForStreamingPlay:(NSString*)cookie;

-(void) setHttpRequestCallback:(void*)callback;


@end


