//
//  Ncg2Agent.h
//  MacNcgSDK
//
//  Created by JinyongPark on 2014. 11. 24..
//  Copyright (c) 2014년 INKAENTWORKS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Ncg2File.h"
#if TARGET_OS_SIMULATOR
#else
    #import "Ncg2FileZip.h"
#endif
#import "Ncg2Webserver.h"
#import "Ncg2SdkCommon.h"


/**
 * @mainpage What's New in NCG iOS
 *
 * @if KOREA
 * @htmlinclude NCG-iOS-SDK.WhatIsNew.html
 * @endif
 * @if ENGLISH
 * @htmlinclude NCG-iOS-SDK.WhatIsNew_Eng.html
 * @endif
 *
 * @ref implementation
 */

/**
 * @page implementation Implementation Guides
 *
 * @if KOREA
 * @htmlinclude NCG-iOS-SDK.Implementation.Guide.html
 * @endif
 * @if ENGLISH
 * @htmlinclude NCG-iOS-SDK.Implementation.Guide_Eng.html
 * @endif
 */


//@protocol NcgHttpAsyncDelegate <NSObject>
//@required
//-(void) onReceiveResponse:(NSString*)header statusCode:(int)code statusMessage:(NSString*)message;
//-(void) onReceiveData:(NSData*)data dataLenght:(int)n;
//-(void) onFail:(NSString*)errorMessage;
//-(void) onComplete;
//
//@end

//---------------------------------------------------------------------------------
// @protocol NcgHttpRequestDelegate
//---------------------------------------------------------------------------------

/**
 * @if KOREA
 * HTTP 통신을 위한 딜리게이트 프로토콜로서 SDK 내부에서 이루어지는 HTTP 통신을 앱에서 대행하고자 할 경우에만 정의하고 사용한다. [OPTIONAL]
 * @endif
 *
 * @if ENGLISH
 * A delegate protocol for HTTP communication. It is for the replacement of internal HTTP communication with the application-side implementation. [OPTIONAL]
 * @endif
 */
@protocol NcgHttpRequestDelegate <NSObject>
@required
/**
 * @if KOREA
 * SDK로 부터 전달된 HTTP 요청을 처리하고 응답 데이터를 반환한다.
 * @param requestURL : 요청 URL
 * @param parameter : GET 방식의 파라미터
 * @param header : 커스텀 헤더 예) Range
 * @return 요청 처리 후 서버로부터의 응답 데이터
 * @endif
 *
 * @if ENGLISH
 * Returns response data after handling HTTP request from the SDK.
 * @param requestURL : request URL
 * @param parameter : GET type parameter
 * @param header : request header ex) Range
 * @return response data from server after handling request
 * @endif
 */
- (NSData *)handleHttpRequest:(NSString *)requestURL urlParameter:(NSString *)parameter requestHeaders:(NSDictionary *)header;

/**
 * @if KOREA
 * 바로 직전에 처리된 요청의 서버 HTTP 응답 코드를 반환한다.
 * @return HTTP 응답 코드 반환
 * @endif
 *
 * @if ENGLISH
 * Returns the HTTP response code from server for the latest request.
 * @return HTTP response code
 * @endif
 */
- (int)getResponseStatus;

/**
 * @if KOREA
 * 바로 직전에 처리된 요청의 서버 응답 메시지를 반환한다.
 * @return HTTP 응답 메시지 반환
 * @endif
 *
 * @if ENGLISH
 * Returns the HTTP response message from server for the latest request.
 * @return HTTP response message
 * @endif
 */
- (NSString *)getResponseMessage;						// 이전 요청의 HTTP 응답 메시지 반환

/**
 * @if KOREA
 * 바로 직전에 처리된 요청의 오류 메시지를 반환한다. 성공인 경우는 빈 문자열을 반환한다.
 * @return HTTP 오류 메시지 반환
 * @endif
 *
 * @if ENGLISH
 * Returns an error message for the latest request. Returns an empty string if it was successful.
 * @return HTTP error message
 * @endif
 */
- (NSString *)getLastErrorMessage;


-(NSDictionary *)getResponseHttpHeader;


@optional

// Do not working.
- (BOOL)httpLwsSendRangeRequest:(NSString *)requestURL urlParameter:(NSString *)parameter requestHeaders:(NSDictionary *)header;

@end






//---------------------------------------------------------------------------------
// @interface Ncg2Agent
//---------------------------------------------------------------------------------

/**
 * @if KOREA
 * Ncg2Agent 클래스는 NCG SDK의 사용하기 위한 주요 클래스이다.<br>
 * NCG SDK 초기화를 위한 initialize 메소드가 존재하며 종료될때에는 clear를 호출해줘야 한다.<br>
 * 해당 클래스는 Singile Instance 로 사용해야 하므로 직접 alloc, init를 호출하는 대신 sharedInstance 메소드를 이용하여
 * 공유된 객체를 획득하여 사용해야 한다.<br>
 * 주요 기능은 라이선스관련기능이며 라이선스 획득시 내부적으로 라이선스서버(RI) 암호화된 통신을 수행할 수 있다.<br>
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
@interface Ncg2Agent : NSObject
@property (nonatomic, retain) id<NcgHttpRequestDelegate> _httpRequestDelegate;

@property (atomic, retain) NSMutableDictionary* callbackFileDic;
@property (atomic, retain) NSMutableDictionary* callbackFileNameDic;
//@property (nonatomic, retain) NSFileHandle* callbackFileHandle;
@property (nonatomic, readwrite) UInt64 currentFilePosition;
//@property (nonatomic, retain) id<NcgHttpAsyncDelegate> _httpAsyncDelegate;


/**
 * @if KOREA
 * Ncg2Agent 객체를 이용하기 위해서는 sharedInstance 를 통해 접근해야 한다.
 * 만약 alloc, init 형태로 객체의 생성을 시도한다면 Exception이 발생되므로 직접 객체생성은 피해야 한다.
 * 아래와 같은 코드로 이용할 수 있다.
 * @code
 * Ncg2Agent* agent = [Ncg2Agent sharedInstance];
 * @endcode
 * @endif
 *
 * @if ENGLISH
 *
 * @code
 * Ncg2Agent* agent = [Ncg2Agent sharedInstance];
 * @endcode
 * @endif
 */
+(id)sharedInstance;


#pragma mark - SDK Initialize And Clear

/**
 * @if KOREA
 * NCG 라이브러리를 사용하기 전 해당 메소드를 호출하여 초기화시켜줘야 한다.<br>
 * 내부적으로 Secure Time값을 체크한다. <br>
 * Secure Time을 획득하기 위해 현재 인터넷이 연결된 상태이면 온라인 타임서버를 통해 SecureTime을 획득한다.<br>
 * 인터넷이 연결되지 않은 상태이면 Device 시간값을 이용하게 된다.<br>
 *
 * @param policy    오프라인 상태를 어떻게 처리할지에 대한 정책 정보.
 * @param rodbPath  라이브러리내에서 사용할 RoDB(라이선스 DB) 경로를 입력한다. nil 입력시 샌드박스 안에 생성된다.
 * @param deviceId  라이브러리내에서 사용할 DeviceID값을 입력한다. nil 입력시 SDK에서 자동 추출한다.
 * @aaram error     nil이 아닌 경우 해당에러를 확인한다.
 * @return          성공이면 YES. 실패면 NO.
 * @endif
 *
 * @if ENGLISH
 * NCG library has to be initialized by calling the relevant method before using it.<br>
 * Secure Time value is verified internally while initialization.<br>
 * If the device is on-line, Secure Time is acquired through on-line time server.<br>
 * Device time value is used if it is not connected with Internet service. <br>
 *
 * @param policy	A policy information that how to process when the device is off-line.
 * @param rodbPath 	the path of RoDB(license DB) which will be used inside of library. If the value is nil, it is created in the sandbox of the application.
 * @param deviceId	the DeviceID which will be used in library. If the value is nil, It is generated automatically by SDK.
 * @param error     check error if nil no. succeeded if nil.
 * @return          YES if succeeded. NO if failed.
 * @endif
 */

-(BOOL) initialize:(OfflineSupportPolicy)policy rodbPath:(NSString*)rodbPath deviceId:(NSString*)deviceId error:(NSError**)error;

/**
 * @if KOREA
 * NCG 라이브러리를 사용하기 전 해당 메소드를 호출하여 초기화시켜줘야 한다.<br>
 * 내부적으로 Secure Time값을 체크한다. <br>
 * Secure Time을 획득하기 위해 현재 인터넷이 연결된 상태이면 온라인 타임서버를 통해 SecureTime을 획득한다.<br>
 * 인터넷이 연결되지 않은 상태이면 Device 시간값을 이용하게 된다.  <br>
 *
 * @param policy            오프라인 상태를 어떻게 처리할지에 대한 정책 정보.
 * @param executionLimit    오프라인 상태에서 재실행 횟수 지정(0이면 무제한).
 * @param rodbPath          라이브러리내에서 사용할 RoDB(라이선스 DB) 경로를 입력한다.  null 입력시 샌드박스 안에 생성된다.
 * @param deviceId          라이브러리내에서 사용할 DeviceID값을 입력한다. null 입력시 SDK에서 자동 추출한다.
 * @aaram error             nil이 아닌 경우 해당에러를 확인한다.
 * @return                  성공이면 YES. 실패면 NO.
 * @endif
 *
 * @if ENGLISH
 * NCG library has to be initialized by calling the relevant method before using it.<br>
 * Secure Time value is verified internally while initialization.<br>
 * If the device is on-line, Secure Time is acquired through on-line time server.<br>
 * Device time value is used if it is not connected with Internet service. <br>
 *
 * @param policy            A policy information that how to process when the device is off-line.
 * @param executionLimit    off-line re-running count(0 if unlimit).
 * @param rodbPath          the path of RoDB(license DB) which will be used inside of library. If the value is null, it is created in the sandbox of the application.
 * @param deviceId          the DeviceID which will be used in library. If the value is null, It is generated automatically by SDK.
 * @param error             check error if nil no. succeeded if nil.
 * @return                  YES if succeeded. NO if failed.
 * @endif
 */
-(BOOL) initialize:(OfflineSupportPolicy)policy executionLimit:(int)executionLimit rodbPath:(NSString*)rodbPath deviceId:(NSString*)deviceId error:(NSError**)error;

/**
 * @if KOREA
 * NCG 라이브러리의 사용을 마친 후에는 해당 메소드를 호출하여 할당된 리소스를 해제해야 한다.
 * @endif
 *
 * @if ENGLISH
 * It has to be released the relevant resource calling the method after using NCG library.
 * @endif
 */
-(void) clear;


#pragma mark - Http Callback(Delegate)

/**
 * @if KOREA
 * NcgHttpRequestDelegate 객체를 SDK에 등록한다.<br>
 * SDK 내부적으로 라이선스서버와의 HTTP 통신이 필요한 경우 해당 객체의 메소드를 호출한다.
 *
 * @param delegate	NcgHttpRequestDelegate 객체
 * @endif
 *
 * @if ENGLISH
 * Register NcgHttpRequestDelegate object on SDK.<br>
 * It calls the method of relevant object when license sever and HTTP communication are needed inside SDK internally.
 *
 * @param delegate NcgHttpRequestDelegate 객체
 * @endif
 */
-(void) setHttpRequestDelegate:(id<NcgHttpRequestDelegate>) delegate;

#pragma mark - Exceptional Event Callback(Delegate)

- (void) setExceptionalEventDelegate:(id<NcgExceptionalEventDelegate>) delegate;

#pragma mark - License Information, Check And Acquisition

/**
 * @if KOREA
 * 파일의 경로를 통해 NCG 컨텐츠의 라이선스가 유효한지를 검증한다.
 * 
 * DRM 라이선스가 존재하고 유효한 상태에서만 NCG 컨텐츠를 이용할 수 있으므로 NCG 컨텐츠를 이용하기 전에 일반적으로 
 * 라이선스가 유효한지를 검증한 후 사용한다.
 *
 * @param path
 * 라이선스를 검증할 NCG 파일의 경로. path는 로컬 경로 혹은 URL로도 전달될 수 있다.
 * @param lv 라이선스 검증결과가 해당 파라미터를 통해서 반환된다.
 * 라이선스 검증이 유효한 경우에는 LV_ValidLicense 값이 반환되며 그 외의 값이 반환된 경우에는 유효하지 않은 경우이다.
 * 아래와 같은 값이 있으며 자세한 정보는 LicenseValidation 의 필드들을 통해 확인할 수 있다.<br>
 * ValidLicense : 유효한 라이선스<br>
 * NotExistLicense : 라이선스가 없음<br>
 * ExpiredLicense : 만료된 라이선스<br>
 * BeforeStartDate : 현재 시간이 재생가능시간보다 이전인 경우.<br>
 * ExceededPlayCount : 재생횟수가 만료된 경우<br>
 * NotRegisteredNcgDevice : 기기가 등록되지 않은 경우.<br>
 * NotSupportOffline : 오프라인상태에서 재생을 지원하지 않는 경우.<br>
 * DetectedDeviceTimeModified : 기기의 시간이 변경된 경우.<br>
 * OfflineTooLong : Offline 상태로 오래 지속된 경우.<br>
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(BOOL) checkLicenseValidByPath:(NSString*)path result:(LicenseValidation*)lv error:(NSError**)error;

/**
 * @if KOREA
 * ContentID를 통해서 라이선스가 유효한지를 검증한다.
 *
 * DRM 라이선스가 존재하고 유효한 상태에서만 NCG 컨텐츠를 이용할 수 있으므로 NCG 컨텐츠를 이용하기 전에 일반적으로
 * 라이선스가 유효한지를 검증한 후 사용한다.
 * @param cid       라이선스를 검증할 cid <br>
 *                  ContentID는  NCG 컨텐츠를 패키징할 때 부여되는 값이며 RI 서버의 DB테이블에도 등록되며 NCG 파일의 헤더에도 Content ID가 기록된다.
 * @param siteID    라이선스를 검증하는 Site ID
 * @param lv        라이선스 검증결과가 해당 파라미터를 통해서 반환된다.
 *                  라이선스 검증이 유효한 경우에는 LV_ValidLicense 값이 반환되며 그 외의 값이 반환된 경우에는 유효하지 않은 경우이다.<br>
 *                  아래와 같은 값이 있으며 자세한 정보는 LicenseValidation 의 필드들을 통해 확인할 수 있다.<br>
 * 
 * LV_ValidLicense : 유효한 라이선스<br>
 * LV_NotExistLicense : 라이선스가 없음<br>
 * LV_ExpiredLicense : 만료된 라이선스<br>
 * LV_BeforeStartDate : 현재 시간이 재생가능시간보다 이전인 경우.<br>
 * LV_ExceededPlayCount : 재생횟수가 만료된 경우<br>
 * LV_NotRegisteredNcgDevice : 기기가 등록되지 않은 경우.<br>
 * LV_NotSupportOffline : 오프라인상태에서 재생을 지원하지 않는 경우.<br>
 * LV_DetectedDeviceTimeModified : 기기의 시간이 변경된 경우.<br>
 * LV_OfflineTooLong : Offline 상태로 오래 지속된 경우.<br>
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(BOOL) checkLicenseValidByCID:(NSString*)cid siteID:(NSString*)siteID result:(LicenseValidation*)lv error:(NSError**)error;

/**
 * @if KOREA
 * 파일의 경로를 통해 NCG 컨텐츠의 라이선스 정보를 획득한다.
 * DRM 라이선스에 대한 정보를 확인하기 위해 사용된다. 라이선스 정보에는 사용 가능한 기간, 횟수등의 정보가 있다.
 *
 * @param path      라이선스정보를 확인할 NCG 파일의 경로. path는 로컬 경로 혹은 URL로도 전달될 수 있다.
 * @param lv        라이선스 검증결과가 해당 파라미터를 통해서 반환된다.
 * @param li        라이선스 정보가 담길 Ncg2LicenseInformation 객체
 * @param error     오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(BOOL) getLicenseInfoByPath:(NSString*)path licenseValidation:(LicenseValidation*)lv licenseInformation:(Ncg2LicenseInformation**)li error:(NSError**)error;

/**
 * @if KOREA
 * ContentID를 통해서 라이선스 정보를 획득한다.
 * DRM 라이선스에 대한 정보를 확인하기 위해 사용된다. 라이선스 정보에는 사용 가능한 기간, 횟수등의 정보가 있다.
 *
 * @param cid       라이선스 정보를 획득할 ContentID <br>
 * ContentID는  NCG 컨텐츠를 패키징할 때 부여되는 값이며 RI 서버의 DB테이블에도 등록되며 NCG 파일의 헤더에도 Content ID가 기록된다.
 * @param siteID    Contents를 배포한 Site의 ID
 * @param lv        라이선스 유효 정보가 담긴 LicenseValidation 객체
 * @param li        라이선스 정보가 담길 Ncg2LicenseInformation 객체
 * @param error     오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(BOOL) getLicenseInfoByCID:(NSString*)cid siteID:(NSString*)siteID licenseValidation:(LicenseValidation*)lv licenseInformation:(Ncg2LicenseInformation**)li error:(NSError**)error;

/**
 * @if KOREA
 * NCG 파일에 대한 라이선스 정보를 라이선스 서버에 요청한다.<br>
 * userID 값은 라이선스 서버가 사용자 인증을 할때 필요하다. <br>
 * orderID 값은 컨텐츠의 주문에 필요한 정보이며, 특별한 경우가 아니면 사용하지 않고 nil/(공백) 값을 입력하면 된다.<br>
 *
 * @param path      NCG 파일 경로 및 URL
 * @param userID    사용자 아이디
 * @param orderID   주문 아이디
 * @param isTemporary 라이선스 저장 여부
 * @param error     획득에 실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다.<br>
 * 기본적으로 오류에 대한 정보는 NSLocalizedDescriptionKey Key로서 자세한 정보를 확인할 수 있다.<br>
 * 또한 userinfo의 key로써 다음과 같은 값을 이용하여 라이선스서버로부터 전달받은 값을 확인할 수 있다.<br>
 * @code
 // 라이선스서버로부터 전달받은 ErrorCode
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // 라이선스서버로부터 전달받은 ErrorMessage
 #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
 * @endcode
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * It requests the license information of NCG file to license sever.<br>
 * userID value is needed for user authentication on license server.<br>
 * orderID value is necessary information to order and it is used only for a special cases. And it can be input null/(blank) value in general cases.
 *
 * @param path	 	NCG file route and URL
 * @param userID 	User ID
 * @param orderID 	Order ID
 * @param isTemporary 라이선스 저장 여부
 * @param error
 * @code
 // Error Code
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // Error Message
 #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
 * @endcode
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) acquireLicenseByPath:(NSString*)path userID:(NSString*)userID orderID:(NSString*)orderID isTemporary:(BOOL)isTemporary error:(NSError**)error;


/**
 * @if KOREA
 * CID의 정보를 통해 라이선스 정보를 라이선스 서버에 요청한다.<br>
 * 해당 메소드는 NCG파일이 없고 라이선스 획득시 필요한 파라미터만 알고 있을때 사용된다. <br>
 * 예를들어, HLS 컨텐츠의 라이선스를 다운로드하기 위해서 사용될 수 있다. <br>
 *
 * @param cid				컨텐츠의 ID
 * @param siteID			Site ID
 * @param userID			사용자 ID
 * @param orderID			주문ID, 선택사양으로써 빈값으로 전달가능하다.
 * @param acquisitionUrl	라이선스서버의 URL
 * @param isTemporary       라이선스 저장 여부(YES, NO)
 * @param error             획득에 실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다.<br>
 * 기본적으로 오류에 대한 정보는 NSLocalizedDescriptionKey Key로서 자세한 정보를 확인할 수 있다.<br>
 * 또한 userinfo의 key로써 다음과 같은 값을 이용하여 라이선스서버로부터 전달받은 값을 확인할 수 있다.<br>
 * @code
 // 라이선스서버로부터 전달받은 ErrorCode
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // 라이선스서버로부터 전달받은 ErrorMessage
 #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
 * @endcode
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * It requests the license information of CID to license sever.<br>
 * It can be used in case that there is no NCG file available and CID value is known for license acquisition.<br>
 * For example, it can be used for playback of HLS contents. <br>
 *
 * @param cid				Content ID
 * @param siteID			Site ID
 * @param userID			User ID
 * @param orderID			Order ID, it is able to transfer as empty value as an option.
 * @param acquisitionUrl	URL for License sever
 * @param isTemporary       License Saved(YES, NO)
 * @param error
 * @code
 // Error Code
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // Error Message
 #define NcgErrorK
 * @endcode
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) acquireLicenseByCID:(NSString*)cid siteID:(NSString*)siteID userID:(NSString*)userID orderID:(NSString*)orderID
             acquisitionUrl:(NSString*)acquisitionUrl isTemporary:(BOOL)isTemporary error:(NSError**)error;

/**
 * @if KOREA
 * acquireLicenseByToken 메소드는 Token 정보를 통해 라이선스 서버에 요청한다.<br>
 * 해당 메소드는 base64 Encoding 된 Token에서 필요한 정보를 추출하여 라이선스를 요청한다. <br>
 * Token은 NCG 헤더 정보 중 Content ID, Site ID, User ID를 포함하고 있어 <br>
 * 라이선스를 획득하기 위해 NCG 파일을 다운로드 받을 필요가 없어진다. <br>
 * 예를들어, HLS, PD 컨텐츠의 라이선스 획득 시 네트워크 리소스를 절약할 수 있다. <br>
 *
 * @param token             token
 * @param isTemporary       License Saved(YES, NO)
 * @param error             획득에 실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다.<br>
 * 기본적으로 오류에 대한 정보는 NSLocalizedDescriptionKey Key로서 자세한 정보를 확인할 수 있다.<br>
 * 또한 userinfo의 key로써 다음과 같은 값을 이용하여 라이선스서버로부터 전달받은 값을 확인할 수 있다.<br>
 * @code
 // 라이선스서버로부터 전달받은 ErrorCode
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // 라이선스서버로부터 전달받은 ErrorMessage
 #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
 * @endcode
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * It requests the license information of Token to license sever.<br>
 * The method extracts the necessary information from the base64 encoded Token and requests the license. <br>
 * The Token contains the Content ID, Site ID, and User ID of the NCG header information, <br>
 * so that it is not necessary to download the NCG file in order to acquire the license. <br>
 * For example, when acquiring license for HLS, PD contents, network resource and time can be saved. <br>
 *
 * @param token             token
 * @param isTemporary       License Saved(YES, NO)
 * @param error
 * @code
 // Error Code
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // Error Message
 #define NcgErrorK
 * @endcode
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) acquireLicenseByToken:(NSString*)token isTemporary:(BOOL)isTemporary error:(NSError**)error;


/**
* @if KOREA
* acquireLicenseByToken 메소드는 Token 정보를 통해 라이선스 서버에 요청한다.<br>
* 해당 메소드는 base64 Encoding 된 Token에서 필요한 정보를 추출하여 라이선스를 요청한다. <br>
* Token은 NCG 헤더 정보 중 Content ID, Site ID, User ID를 포함하고 있어 <br>
* 라이선스를 획득하기 위해 NCG 파일을 다운로드 받을 필요가 없어진다. <br>
* 예를들어, HLS, PD 컨텐츠의 라이선스 획득 시 네트워크 리소스를 절약할 수 있다. <br>
*
* @param token             token
* @param acquisitionUrl    라이선스서버의 URL(default:PallyCon Server)
* @param isTemporary       License Saved(YES, NO)
* @param error             획득에 실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다.<br>
* 기본적으로 오류에 대한 정보는 NSLocalizedDescriptionKey Key로서 자세한 정보를 확인할 수 있다.<br>
* 또한 userinfo의 key로써 다음과 같은 값을 이용하여 라이선스서버로부터 전달받은 값을 확인할 수 있다.<br>
* @code
// 라이선스서버로부터 전달받은 ErrorCode
#define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
// 라이선스서버로부터 전달받은 ErrorMessage
#define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
* @endcode
* @return 성공여부를 반환한다.
* @endif
*
* @if ENGLISH
* It requests the license information of Token to license sever.<br>
* The method extracts the necessary information from the base64 encoded Token and requests the license. <br>
* The Token contains the Content ID, Site ID, and User ID of the NCG header information, <br>
* so that it is not necessary to download the NCG file in order to acquire the license. <br>
* For example, when acquiring license for HLS, PD contents, network resource and time can be saved. <br>
*
* @param token             token
* @param acquisitionUrl    URL for License sever(default:PallyCon Server)
* @param isTemporary       License Saved(YES, NO)
* @param error
* @code
// Error Code
#define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
// Error Message
#define NcgErrorK
* @endcode
* @return YES if Succeeded, NO if Fail.
* @endif
*/
-(BOOL) acquireLicenseByToken:(NSString*)token acquisitionUrl:(NSString*)acquisitionUrl isTemporary:(BOOL)isTemporary error:(NSError**)error;


/**
 * @if KOREA
 * acquireLicenseByToken 메소드는 Token 정보를 통해 라이선스 서버에 요청한다.<br>
 * 해당 메소드는 NCG파일이 없고 라이선스 획득시 필요한 파라미터만 알고 있을때도 사용된다. <br>
 * 예를들어, HLS 컨텐츠의 라이선스를 다운로드하기 위해서 사용될 수 있다. <br>
 *
 * @param token				token
 * @param cid				컨텐츠의 ID
 * @param siteID			Site ID
 * @param userID			사용자 ID
 * @param acquisitionUrl	라이선스서버의 URL(default:PallyCon Server)
 * @param isTemporary       라이선스 저장 여부(YES, NO)
 * @param error             획득에 실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다.<br>
 * 기본적으로 오류에 대한 정보는 NSLocalizedDescriptionKey Key로서 자세한 정보를 확인할 수 있다.<br>
 * 또한 userinfo의 key로써 다음과 같은 값을 이용하여 라이선스서버로부터 전달받은 값을 확인할 수 있다.<br>
 * @code
 // 라이선스서버로부터 전달받은 ErrorCode
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // 라이선스서버로부터 전달받은 ErrorMessage
 #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
 * @endcode
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * It requests the license information of Token to license sever.<br>
 * It can be used in case that there is no NCG file available and CID value is known for license acquisition.<br>
 * For example, it can be used for playback of HLS contents. <br>
 *
 * @param token				token
 * @param cid				Content ID
 * @param siteID			Site ID
 * @param userID			User ID
 * @param acquisitionUrl	URL for License sever(default:PallyCon Server)
 * @param isTemporary       License Saved(YES, NO)
 * @param error
 * @code
 // Error Code
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // Error Message
 #define NcgErrorK
 * @endcode
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) acquireLicenseByToken:(NSString*)token cid:(NSString*)cid siteID:(NSString*)siteID userID:(NSString*)userID
               acquisitionUrl:(NSString*)acquisitionUrl isTemporary:(BOOL)isTemporary error:(NSError**)error;


/**
 * @if KOREA
 * 주어진 Token에서 정보를 추출하여 반환됩니다.
 *
 * @param token     PallyCon Token
 * @param error    When an error occurs, an error object is passed to check the error information in detail.
 * @return 성공 시 Ncg2TokenInfo 를 반환하고 실패 시 nil를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * It is returned by extracting information from the given token.
 *
 * @param token   PallyCon Token
 * @param error   When an error occurs, an error object is passed to check the error information in detail.
 * @return On success, Ncg2TokenInfo is returned, and on failure, nil is returned.
 * @endif
 */
-(Ncg2TokenInfo*) getTokenInfo:(NSString*)token error:(NSError**)error;


/**
 * @if KOREA
 * 입력된 NCG 파일의 횟수를 차감한다.
 *
 * @param path NCG 파일 경로
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * Decrease Playback count of NCG file.
 *
 * @param path 		NCG file route
 * @param error
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
- (BOOL) decreasePlaybackCount:(NSString*)path error:(NSError**)error;


#pragma mark - License Remove

/**
 * @if KOREA
 * 입력된 NCG 파일의 DRM 라이선스 정보를 라이선스 DB에서 삭제한다.
 *
 * @param path  NCG 파일 경로
 * @param error 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * Remove a input license information of NCG file from lincese DB of device.
 *
 * @param path 		NCG file route
 * @param error
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) removeLicenseByPath:(NSString*)path error:(NSError**)error;


/**
 * @if KOREA
 * NCG 파일과 연결된 DRM 라이선스를 삭제한다.<br>
 * 해당 파일은, 라이선스를 다시 획득할 때까지 사용할 수 없다.
 *
 * @param cid       컨텐츠ID
 * @param error     오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 * Removes contents license which are connected with NCG file.<br>
 * The relevant file can not be used until acquiring the license again.
 *
 * @param cid       Contents ID
 * @param error
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) removeLicenseByCID:(NSString*)cid error:(NSError**)error;

-(BOOL) removeLicenseByCID:(NSString*)cid siteID:(NSString*)siteID error:(NSError**)error;


/**
 * @if KOREA
 * 라이선스를 발급을 ONE_TIME 으로 선택했을 경우 메모리상에 라이선스를 삭제한다.<br>
 * 라이선스를 발급 받을 때 RODB에 저장하지 않는 경우(DB_SAVE) 반드시 호출해줘야 라이선스를 메모리에서 삭제하여
 * 다음 라이선스 획득시 라이선스 서버에서 받게된다.
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @param error
 * @return YES if Succeeded, NO if Fail.
 * @endif
 */
-(BOOL) removeAllTemporaryLicense:(NSError**)error;

#pragma mark - DRM File
/**
 * @if KOREA
 * 지정된 경로의 파일이 NCG 컨텐츠인지 아닌지를 판별한다.
 *
 * @param path
 * NCG 컨텐츠인지를 확인할 path이며 로컬 경로 혹은 URL로도 전달될 수 있다.
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(BOOL) isNcgContent:(NSString*)path error:(NSError**)error;

/**
 * @if KOREA
 * Ncg2File객체를 생성한다.
 * Ncg2File객체는 직접 객체를 생성하는 대신 해당 메소드를 통해 생성해야 한다.
 * @return Ncg2File 객체를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(Ncg2File*) createNcgFile:(NSError**)error;

#if TARGET_OS_SIMULATOR
#else
    -(Ncg2FileZip*) createNcgFileZip:(NSError**)error;
#endif

/**
 * @if KOREA
 * NCG 파일의 헤더 정보 내용을 반환한다.<br>
 *
 * @param path  NCG파일의 경로. 로컬경로 혹은 URL경로가 될 수 있다.
 * @param error 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return Ncg2HeaderInformation 객체를 반환한다. 만약 오류가 발생된 경우에는 nil로 반환된다.
 * @endif
 *
 * @if ENGLISH
 * Read and bring the Header information of NCG file.<br>
 *
 * @param path     NCG file's route
 * @param error
 * @return Ncg2HeaderInformation object, nil if failed.
 * @endif
 */
-(Ncg2HeaderInformation*) getNcg2HeaderInfo:(NSString*)path error:(NSError**)error;

#pragma mark - Secure Time
/**
 * @if KOREA
 * SDK 내부에서 운용되는 시간을 반환한다.
 *
 * @return GMT 시간 문자열 반환
 * @endif
 *
 * @if ENGLISH
 * @return GMT Time.
 * @endif
 */
-(NSString*) getNcgSecureTime;

/**
 * @if KOREA
 * SecureTime을 업데이트한다.
 * DeviceTime이 변경되었거나 Offline으로 실행된 횟수가 많아 온라인연결이 필요한 경우<br>
 * 해당 메소드를 호출하여 SecureTime을 업데이트할 수 있다.
 * lv 값이 아래에 해당되는 경우 해당 메소드를 호출하여 SecureTime을 갱신하면 라이선스를 재검증할 수 있게 된다.
 * LV_DetectedDeviceTimeModified, LV_OfflineTooLong
 * @param error 오류를 반환한다.
 * @return 성공여부
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(BOOL) updateSecureTimeFromServer:(NSError**)error;

#pragma mark - Local web server
/**
 * @if KOREA
 * 생성된 로컬 웹서버 인스턴스를 얻는다.
 * @return 성공 시 Ncg2Webserver 객체를 반환한다.
 * @endif
 *
 * @if ENGLISH
 *
 * @return Ncg2Webserver Object if succeeded
 * @endif
 */
-(Ncg2Webserver*) getLocalWebServerInstance;

#pragma mark -
/**
 * @if KOREA
 * DeviceID를 반환한다.
 * @param error 오류를 반환한다. 성공 시 nil.
 * @return DeviceID 문자열
 * @endif
 *
 * @if ENGLISH
 * @param error
 * @return Device ID string.
 * @endif
 */
-(nullable NSString*) getNcgDeviceID:(NSError* _Nullable *_Nullable)error;


/**
 * @if KOREA
 * NCG 라이선스 서버와 Custom 통신을 수행한다. <br>
 *
 * 라이선스 서버와의 통신시에는 PKI 형태의 Secure-Channel이 이루어지므로 안전하게 서버와 데이터를 주고 받기 위해 사용될 수 있다.
 * 해당 메소드에서는 라이선스 서버로 HTTP Request가 전송되며 라이선스 서버는 GateWay페이지를 호출하게 되어 GateWay페이지에서 해당 요청에 대한 응답을 할 수 있게 한다.
 * @param acquisitionUrl    LicenseServer URL
 * @param siteID            Site ID
 * @param requestData       Request Data
 * @param error             실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다.<br>
 * 기본적으로 오류에 대한 정보는 NSLocalizedDescriptionKey Key로서 자세한 정보를 확인할 수 있다.<br>
 * 또한 userinfo의 key로써 다음과 같은 값을 이용하여 라이선스서버로부터 전달받은 값을 확인할 수 있다.<br>
 * @code
 // 라이선스서버로부터 전달받은 ErrorCode
 #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 // 라이선스서버로부터 전달받은 ErrorMessage
 #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
 * @endcode
 * @return 라이선스 서버로부터 획득한 Response 데이터를 문자열로 반환한다.
 * @endif
 *
 * @if ENGLISH
 * Send a custom request to NCG License-Server.
 *
 * NCG Licese-Server can be comunicated with Client SDK by PKI Secure-Channel.
 * This method provides some kind of Custom PKI Secure-Channel.
 * This method sends a custom request to the License-Server and then the License-Server redirect the request to gateway-page to process the request.
 * The response data that gateway-page responded is returned to license-server and then license-server respond the data to Client SDK.
 *
 * @param acquisitionUrl    LicenseServer URL
 * @param siteID            siteID
 * @param requestData       request data
 * @param error             실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다
 * @return Response string that the license-server responded
 * @endif
 */
-(NSString*) sendCustomRequest:(NSString*)acquisitionUrl
                        siteID:(NSString*)siteID
                    requestData:(NSString*)requestData
                         error:(NSError**)error;

/**
 * @if KOREA
 * PallyCon을 사용하는 콘텐츠 서비스 업체 대한 인증을 요청한다. <br>
 *
 * PallyCon 서비스는 하나의 라이선스 서버에 여러 서비스 업체가 연결되어 사용하므로 해당 업체가 PallyCon을 사용여부를 확인해야 한다.
 * 해당 메소드는 PallyCon 서비스를 사용하는 업체가 SDK를 이용하여 Application을 개발할 때 디바이스 정보 등록 전에 호출되줘야 한다.
 * @param acquisitionUrl LicenseServer URL
 * @param responseData 라이선스 서버로부터 획득한 Response 데이터를 문자열
 * @param error 실패한 경우 해당 error객체를 통해 자세한 정보를 확인할 수 있다
 * @return 성공(0) 혹은 에러코드 반환
 * @endif
 *
 * @if ENGLISH
 *
 * @return 0 if succeeded. An error code if failed.
 * @endif
 */
-(NSString*) pallyconVendorRegistration:(NSString*)acquisitionUrl error:(NSError**)error;

/**
 * @if KOREA
 * 로그를 활성화시킨다.
 * @endif
 *
 * @if ENGLISH
 * Activate Log.
 * @endif
 */
-(void) enableLog;

/**
 * @if KOREA
 * 로그를 비활성화시킨다.
 *
 * 대부분의 로그를 비활성화시키지만 오류정보는 출력될 수 있다.
 * @endif
 *
 * @if ENGLISH
 * Deactivate Log. It is to deactivated most logs but error information can be output.
 * @endif
 */
-(void) disableLog;

/**
 * @if KOREA
 * Screen Recorder App 검출 기능을 설정할 수 있다.
 * @param enabled 검출 기능 on/off
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(void) setScreenRecorderAppDetecting:(BOOL)enabled;

/**
 * @if KOREA
 * Screen Recorder가 발견되었을 경우 해당 앱 정보를 리턴한다..
 * @endif
 *
 * @if ENGLISH
 *
 * @endif
 */
-(NSString*) getDetectedScreenRecorderName;


#pragma mark - HTTP Async Delegate

-(int) onReceiveResponseHeader:(NSString*)header statusCode:(int)code statusMessage:(NSString*)message;
-(int) onReceiveData:(NSData*)data dataLenght:(int)n;
-(void) onFail:(NSString*)errorMessage;
-(void) onComplete;


@end


