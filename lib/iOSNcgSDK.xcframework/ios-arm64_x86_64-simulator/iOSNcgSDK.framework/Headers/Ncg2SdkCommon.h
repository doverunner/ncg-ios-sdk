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

//---------------------------------------------------------------------------------
// @protocol NcgExceptionalEventDelegate
//---------------------------------------------------------------------------------

@protocol NcgExceptionalEventDelegate <NSObject>
@optional

-(void)log:(NSString*)logMessage;
-(void)logHandle:(NSError*)error;

@end

/**
 * @if KOREA
 * Ncg2Agent.initialize 에 전달되는 파라미터 중 오프라인 지원 정책
 * @endif
 *
 * @if ENGLISH
 * @endif
 */
typedef enum _OfflineSupportPolicy
{
    OfflineSupportNo = 1,
    OfflineSupportYes = 2,
} OfflineSupportPolicy;

//-----------------------------------------------------------------------------
// LicenseValidation
//-----------------------------------------------------------------------------
/**
 * @if KOREA
 * 라이선스 유효성을 나타내기 위한 enum
 * @endif
 *
 * @if ENGLISH
 * @endif
 */
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
/**
 * @if KOREA
 * NCG 파일헤더 정보 클래스.
 * NCG 파일의 헤더에 기록된 정보를 표현한다.
 * @endif
 *
 * @if ENGLISH
 * NCG file header information class
 * @endif
 */
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

@property(nonatomic, strong) NSString* contentID;
@property(nonatomic, strong) NSString* siteID;
@property(nonatomic, strong) NSString* acquisitionUrl;
@property(nonatomic, strong) NSString* source;
@property(nonatomic, strong) NSString* packDate;
@property(nonatomic, assign) int encryptionLevel;
@property(nonatomic, assign) int encryptionRange;
@end // @interface Ncg2HeaderInformation

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
/**
 * @if KOREA
 * NCG 컨텐츠의 재생권한정보 클래스
 * @endif
 *
 * @if ENGLISH
 * Play rights information class of NCG contents
 * @endif
 */
@interface Ncg2LicenseInformation : NSObject
/**
 * @if KOREA
 * 재생가능기간의 시작
 * @endif
 *
 * @if ENGLISH
 * Start date of playable period.
 * @endif
 */
-(NSString*) getPlayStartDate;

/**
 * @if KOREA
 * 재생가능기간의 끝
 * @endif
 *
 * @if ENGLISH
 * End date of playable period.
 * @endif
 */
-(NSString*) getPlayEndDate;

/**
 * @if KOREA
 * 재생가능기간의 끝
 * @endif
 *
 * @if ENGLISH
 * End date of playable period.
 * @endif
 */
-(long) getPlayFirstDate;


/**
 * @if KOREA
 * 검증 모드이다.
 * online, offline 이 될 수 있다.
 * @endif
 *
 * @if ENGLISH
 * It is verification mode. It could be on-line or off-line.
 * @endif
 */
-(NSString*) getPlayVerificationMethod;

/**
 * @if KOREA
 * 재생기간 시간값
 * 해당 값이 0이 아니면 처음 재생후 설정된 시간값 만큼 재생이 가능하다.
 * 만약 24라는 값이 존재한다면 처음 재생 후 1일동안 재생이 가능한 컨텐츠인 것이다.
 * @endif
 *
 * @if ENGLISH
 * If the play duration value is not zero(0), it is able to play as much as setting time vale after the first time to play.
 * And if there is 24-hour value, it is the content which is able to play for one day after first time to be played.
 * @endif
 */
-(long) getPlayDurationHour;

/**
 * @if KOREA
 * 전체 재생가능한 횟수
 * @endif
 *
 * @if ENGLISH
 * Play total count
 * @endif
 */
-(long) getPlayTotalCount;

/**
 * @if KOREA
 * 현재 남은 재생가능한 횟수.
 * @endif
 *
 * @if ENGLISH
 * Play remained current count.
 * @endif
 */
-(long) getPlayRemainCount;

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


typedef enum _DrmType
{
    playready = 0,
    widevine = 1,
    fairplay = 2,
    ncg = 3
} DrmType;


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

