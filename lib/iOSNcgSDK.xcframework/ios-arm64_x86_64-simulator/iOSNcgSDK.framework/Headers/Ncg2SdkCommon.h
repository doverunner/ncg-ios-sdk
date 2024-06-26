//
//  Ncg2SdkCommon.h
//  MacNcgSDK
//
//  Created by JinyongPark on 2014. 11. 26..
//  Copyright (c) 2014 INKAENTWORKS. All rights reserved.
//

#import <Foundation/Foundation.h>


//
// Dictionary Key Value For NSError Loopup.
//
#define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
#define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"

// ALL < DEBUG < INFO < ERROR < FATAL < OFF
/*
# Log Level
# TRACE : 추적 레벨은 Debug보다 좀더 상세한 정보를 나타냄
# DEBUG : 프로그램을 디버깅하기 위한 정보 지정
# INFO :  상태변경과 같은 정보성 메시지를 나타냄
# WARN :  처리 가능한 문제, 향후 시스템 에러의 원인이 될 수 있는 경고성 메시지를 나타냄
# ERROR :  요청을 처리하는 중 문제가 발생한 경우
# FATAL :  아주 심각한 에러가 발생한 상태, 시스템적으로 심각한 문제가 발생해서 어플리케이션 작동이 불가능할 경우
*/

/// NCG Log Type
typedef enum NCG_LOG_TYPE: int {
    /// All log
    NCG_ALL = 0,
    /// debug log
    NCG_DEBUG = 5,
    /// info log
    NCG_INFO = 6,
    /// error log
    NCG_ERROR = 7,
    /// fault log
    NCG_FAULT = 8,
    /// default value
    NCG_DEFAULT = 9
} LogType;

//---------------------------------------------------------------------------------
// @protocol NcgExceptionalEventDelegate
//---------------------------------------------------------------------------------

/// Log event delegate
@protocol NcgExceptionalEventDelegate <NSObject>
@optional

/// Return log message.
/// - Parameter logMessage: log message.
-(void)log:(NSString*)logMessage;


/// Return ``Error`` object.
/// - Parameter error: ``Error``
-(void)logHandle:(NSError*)error;


/// Returns an error message with ``NCG_LOG_TYPE-c.enum``.
/// - Parameters:
///   - type: ``NCG_LOG_TYPE-c.enum``.
///   - message: error message.
-(void)log:(LogType)type comment:(NSString*)message;

@end

/// Offline support policy for SDK operation.
typedef enum _OfflineSupportPolicy
{
    OfflineSupportNo = 1,
    OfflineSupportYes = 2,
} OfflineSupportPolicy;

//-----------------------------------------------------------------------------
// LicenseValidation
//-----------------------------------------------------------------------------

/// Enumeration to indicate the license check result of NCG content
typedef enum _LicenseValidation
{
    /**
     * @if KOREA
     *	유효한 라이선스가 존재하는 경우
     * @endif
     *
     * @if ENGLISH
     *	the case there is no valid license.
     * @endif
     */
    LicenseValidationValid = 0,
    
    /**
     * @if KOREA
     * 라이선스가 없는 경우
     * @endif
     *
     * @if ENGLISH
     * The case there is no license
     * @endif
     */
    LicenseValidationNotExist,
    
    /**
     * @if KOREA
     * 재생가능 기간이 만료된 경우
     * @endif
     *
     * @if ENGLISH
     * Case which playable period is expired.
     * @endif
     */
    LicenseValidationExpired,
    
    /**
     * @if KOREA
     * 재생가능 시작시간 이전인 경우.
     * @endif
     *
     * @if ENGLISH
     * Case which playable date not available yet.
     * @endif
     */
    LicenseValidationBeforeStartDate,
    
    /**
     * @if KOREA
     * 재생횟수가 만료된 경우
     * @endif
     *
     * @if ENGLISH
     * Play count expired case
     * @endif
     */
    LicenseValidationExceededPlayCount,
    
    /**
     * @if KOREA
     * 현재 해당 컨텐츠는 외부 출력이 불가능한 컨텐츠이며, 현재 디바이스가 외부 출력장치와 연결되어 있는 상태.
     * @endif
     *
     * @if ENGLISH
     * It is the Content which is not allowed output device, but it is not able to play because of connecting with ExternalDevice.
     * @endif
     */
    LicenseValidationExternalDeviceDisallowed,
    
    /**
     * @if KOREA
     * 오프라인환경을 지원하지 않는 정책으로 초기화를 시도하는 과정에서 서버와 접속이 실패되어 오프라인으로 감지된 경우를 나타낸다.
     * 라이선스 체크시 해당 값이 반환된 경우, 온라인 상태로 전환 후 updateSecureTime()을 한번 호출하면 해당 오류상태를 피할 수 있다.
     * @endif
     *
     * @if ENGLISH
     *
     * @endif
     */
    LicenseValidationNotSupportOffline,
    
    /**
     * @if KOREA
     * DeviceTime이  변경된 것을 감지한 경우를 나타낸다.
     * 라이선스 체크시 해당 값이 반환된 경우, 온라인 상태로 전환 후 updateSecureTime()을 한번 호출하면 해당 오류상태를 피할 수 있다.
     * @endif
     *
     * @if ENGLISH
     *
     * @endif
     */
    LicenseValidationDetectedDeviceTimeModified,
    
    /**
     * @if KOREA
     * 루팅된 환경에서 재생을 허용하지 않은 컨텐츠인데 루팅된 단말로 인식된 경우
     * @endif
     *
     * @if ENGLISH
     * It is content which is not allowed to play in rooting condition, but it is recognized as rooting device.
     * @endif
     */
    LicenseValidationAbnormalDevice,
    
    /**
     * @if KOREA
     * Offline으로 실행된 경우가 너무 많아서 온라인이 필요한 상태.
     * 라이선스 체크시 해당 값이 반환된 경우, 온라인 상태로 전환 후 updateSecureTime()을 한번 호출하면 해당 오류상태를 피할 수 있다.
     * @endif
     *
     * @if ENGLISH
     *
     * @endif
     */
    LicenseValidationOfflineTooLong,
    
    /**
     * @if KOREA
     * Screen Recording App 이 설치되어 있을 경우
     * [Ncg2Agent getScreenRecorderAppName]을 호출하여 앱정보를 확인하고 앱을 삭제해야 한다.
     * @endif
     *
     * @if ENGLISH
     *
     * @endif
     */
    LicenseValidationScreenRecorderDetected,
}LicenseValidation;


//-----------------------------------------------------------------------------
// @interface Ncg2HeaderInformation
//-----------------------------------------------------------------------------

/// NCG file header information class
@interface Ncg2HeaderInformation : NSObject
/**
 * @if KOREA
 * 컨텐츠 ID
 * @endif
 *
 * @if ENGLISH
 * Content ID
 * @endif
 */
-(NSString*) contentID;

/**
 * @if KOREA
 * 사이트 ID
 * @endif
 *
 * @if ENGLISH
 * Site ID
 * @endif
 */
-(NSString*) siteID;

/**
 * @if KOREA
 * Acquisition URL(라이선스 획득 URL)
 * @endif
 *
 * @if ENGLISH
 * Acquisition URL
 * @endif
 */
-(NSString*) acquisitionUrl;

/**
 * @if KOREA
 * 서비스 제공 업체 정보
 * @endif
 *
 * @if ENGLISH
 * Contents Provider
 * @endif
 */
-(NSString*) source;

/**
 * @if KOREA
 * 패키징된 날짜 (GMT 기준)
 * @endif
 *
 * @if ENGLISH
 * Packaged Date (GMT standards)
 * @endif
 */
-(NSString*) packDate;

/**
 * @if KOREA
 * Encryption Level
 * @endif
 *
 * @if ENGLISH
 * Encryption Level
 * @endif
 */
-(int) encryptionLevel;

/**
 * @if KOREA
 * Encryption Block Range
 * @endif
 *
 * @if ENGLISH
 * Encryption Block Range
 * @endif
 */
-(int) encryptionRange;

/// content id.
@property(nonatomic, strong) NSString* contentID;
/// site id.
@property(nonatomic, strong) NSString* siteID;
/// acquisition url.
@property(nonatomic, strong) NSString* acquisitionUrl;
/// Contents Provider.
@property(nonatomic, strong) NSString* source;
/// package date.
@property(nonatomic, strong) NSString* packDate;
/// encryption level.
@property(nonatomic, assign) int encryptionLevel;
/// encryption range.
@property(nonatomic, assign) int encryptionRange;
@end // @interface Ncg2HeaderInformation

/// Output Protection Permission.
@interface Ncg2LicenseOutputProtectionPermission : NSObject

-(bool) getIsExternalDisplayAllow;              // outputprotection externaldisplay attribute ( 'a' : allow, 'd' : disallow )
-(int) getAps;                                  // outputprotection aps( 0, 1, 2, 3 )
-(int) getCgms_a;                               // outputprotection cgms-a( 0, 1, 2, 3 )
-(int) getCavendish;                            // outputprotection cavendish
-(int) getHdcp;                                 // outputprotection hdcp
-(bool) getIsJailBreakAllow;                    // ( 'a' : allow, 'd' : disallow )
-(int) getSendReport;                           // abnormaldevice sendreport( 0, 1 )
-(int) getIsJailBreakExternalDisplayAllow;		// abd_externaldisplay_allow( 'a' : allow, 'd' : disallow )

@property(nonatomic, assign) bool isExternalDisplayAllow;
@property(nonatomic, assign) int aps;
@property(nonatomic, assign) int cgms_a;
@property(nonatomic, assign) int cavendish;
@property(nonatomic, assign) int hdcp;
@property(nonatomic, assign) bool isJailBreakAllow;
@property(nonatomic, assign) int isJailBreakExternalDisplayAllow;
@property(nonatomic, assign) int sendReport;
@end


//-----------------------------------------------------------------------------
// @interface Ncg2LicenseInformation
//-----------------------------------------------------------------------------

/// Play rights information class of NCG contents
@interface Ncg2LicenseInformation : NSObject
/// Start date of playable period.
-(NSString*) getPlayStartDate;
/// End date of playable period.
-(NSString*) getPlayEndDate;
/// End date of playable period.
-(long) getPlayFirstDate;
/// It is verification mode. It could be on-line or off-line.
-(NSString*) getPlayVerificationMethod;
/// If the play duration value is not zero(0), it is able to play as much as setting time vale after the first time to play.
/// And if there is 24-hour value, it is the content which is able to play for one day after first time to be played.
-(long) getPlayDurationHour;
/// Play total count
-(long) getPlayTotalCount;
/// Play remained current count.
-(long) getPlayRemainCount;
/// Output protection permission
-(Ncg2LicenseOutputProtectionPermission *) getOutputProtectionPermission;

@property(nonatomic, strong) NSString* playStartDate;
@property(nonatomic, strong) NSString* playEndDate;
@property(nonatomic, assign) unsigned long playFirstDate;
@property(nonatomic, strong) NSString* playVerificationMethod;
@property(nonatomic, assign) long playDurationHour;
@property(nonatomic, assign) long playTotalCount;
@property(nonatomic, assign) long playRemainCount;
@property(nonatomic, retain) Ncg2LicenseOutputProtectionPermission* outputProtectionPermission;

@end // @interface Ncg2LicenseInformation

/// DRM TYPE
typedef enum _DrmType
{
    playready = 0,
    widevine = 1,
    fairplay = 2,
    ncg = 3
} DrmType;

/// Token Information.
@interface Ncg2TokenInfo : NSObject

-(NSString*) getContentID;
-(NSString*) getSiteID;
-(NSString*) getUserID;
-(NSString*) getPolicy;
-(DrmType) getDrmType;
-(BOOL) getKeyRotation;

@property(nonatomic, strong) NSString* contentId;
@property(nonatomic, strong) NSString* siteId;
@property(nonatomic, strong) NSString* userId;
@property(nonatomic, strong) NSString* policy;
@property(nonatomic, assign) DrmType drmType;
@property(nonatomic, assign) BOOL keyRotation;

@end

