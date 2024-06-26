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



/// A delegate protocol for HTTP communication. It is for the replacement of internal HTTP communication with the application-side implementation. [OPTIONAL]
@protocol NcgHttpRequestDelegate <NSObject>
@required

/// Returns response data after handling HTTP request from the SDK.
///  - Parameters:
///    - requestURL: request URL
///    - parameter: GET type parameter
///    - header: request header ex) Range
///  - Returns: response data from server after handling request
- (NSData*)handleHttpRequest:(NSString*)requestURL urlParameter:(NSString*)parameter requestHeaders:(NSDictionary*)header;

/// Returns the HTTP response code from server for the latest request.
/// - Returns: HTTP response code
- (int)getResponseStatus;

/// Returns the HTTP response message from server for the latest request.
/// - Returns: HTTP response message
- (NSString *)getResponseMessage;						// 이전 요청의 HTTP 응답 메시지 반환

/// Returns an error message for the latest request. Returns an empty string if it was successful.
/// - Returns: HTTP error message
- (NSString *)getLastErrorMessage;

/// Returns HttpHeader for the latest request. Returns an empty string if it was successful.
/// - Returns: Http Header
-(NSDictionary *)getResponseHttpHeader;


@optional

/// Do not working.
- (BOOL)httpLwsSendRangeRequest:(NSString *)requestURL urlParameter:(NSString *)parameter requestHeaders:(NSDictionary *)header;

@end




//---------------------------------------------------------------------------------
// @interface Ncg2Agent
//---------------------------------------------------------------------------------

/// The ``Ncg2Agent`` class is the main class for using the NCG SDK.
/// It has an ``initialize:rodbPath:deviceId:error:``method for initializing the NCG SDK and should call clear on exit.
/// This class should be used as a singleton instance, so instead of calling alloc, init directly, you should use the ``sharedInstance`` method to get and use a shared object.
/// Its main function is to get/store and validate licenses.
@interface Ncg2Agent : NSObject
@property (nonatomic, retain) id<NcgHttpRequestDelegate> _httpRequestDelegate;
@property (atomic, retain) NSMutableDictionary* callbackFileDic;
@property (atomic, retain) NSMutableDictionary* callbackFileNameDic;
@property (nonatomic, readwrite) UInt64 currentFilePosition;
//@property (nonatomic, retain) NSFileHandle* callbackFileHandle;
//@property (nonatomic, retain) id<NcgHttpAsyncDelegate> _httpAsyncDelegate;


/// To use the ``Ncg2Agent`` object, you need to access it through ``sharedInstance``.
/// If you try to create an object with alloc or init, an exception will be thrown, so you should avoid creating an object directly.
/// You can use it with the following code.
///
/// - Returns: Returns an ``Ncg2Agent`` instance.
///
/// ```objectivec
/// Ncg2Agent* agent = [Ncg2Agent sharedInstance];
/// ```
+(id)sharedInstance;


#pragma mark - SDK Initialize And Clear



/// NCG library has to be initialized by calling the relevant method before using it.
/// @param policy A policy information that how to process when the device is off-line.
/// @param rodbPath the path of RoDB(license DB) which will be used inside of library. If the value is nil, it is created in the sandbox of the application.
/// @param deviceId the DeviceID which will be used in library. If the value is nil, It is generated automatically by SDK.
/// @param error check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note: **Secure Time** value is verified internally while initialization.
/// If the device is on-line, Secure Time is acquired through on-line time server.
/// Device time value is used if it is not connected with Internet service.
-(BOOL) initialize:(OfflineSupportPolicy)policy rodbPath:(NSString*)rodbPath deviceId:(NSString*)deviceId error:(NSError**)error;


/// NCG library has to be initialized by calling the relevant method before using it.
/// @param policy            A policy information that how to process when the device is off-line.
/// @param executionLimit    off-line re-running count(0 if unlimit).
/// @param rodbPath          the path of RoDB(license DB) which will be used inside of library. If the value is null, it is created in the sandbox of the application.
/// @param deviceId          the DeviceID which will be used in library. If the value is null, It is generated automatically by SDK.
/// @param error             check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note :  **Secure Time** value is verified internally while initialization.
/// If the device is on-line, Secure Time is acquired through on-line time server.
/// Device time value is used if it is not connected with Internet service.
-(BOOL) initialize:(OfflineSupportPolicy)policy executionLimit:(int)executionLimit rodbPath:(NSString*)rodbPath deviceId:(NSString*)deviceId error:(NSError**)error;

/// It has to be released the relevant resource calling the method after using NCG library.
-(void) clear;

#pragma mark - Acquiring and verifying licenses with tokens

/// Check the license with token.
///
/// - Parameters:
///    - token: PallyCon Token
///    - lv: ``LicenseValidation``
///    - error: check error if nil no. succeeded if nil.
/// - Returns: YES if Succeeded, NO if Fail.
-(BOOL) checkLicenseValidByToken:(NSString*)token result:(LicenseValidation*)lv error:(NSError**)error;

/// Acquire a license with a token.
/// The method extracts the necessary information from the base64 encoded Token and requests the license.
/// The token contains information that can be used to obtain a license (Content ID, Site ID, etc.).
/// If you use a token, you can obtain a license faster than an NCG content file (NCG File Paht/URL).
///
/// - Parameters:
///   - token: PallyCon Token
///   - isTemporary: Whether to store the license in the DB. If false, save the license.
///   - error: check error if nil no. succeeded if nil.
/// - Returns: TRUE if Succeeded, FALSE if Fail.
-(BOOL) acquireLicenseByToken:(NSString*)token isTemporary:(BOOL)isTemporary error:(NSError**)error;

/// Acquire a license with a token.
///
/// - Parameters:
///   - token: PallyCon Token
///   - acquisitionUrl: URL for License sever(default:PallyCon Server)
///   - isTemporary: Whether to store the license in the DB. If false, save the license.
///   - error: check error if nil no. succeeded if nil.
/// - Returns: TRUE if Succeeded, FALSE if Fail.
-(BOOL) acquireLicenseByToken:(NSString*)token acquisitionUrl:(NSString*)acquisitionUrl isTemporary:(BOOL)isTemporary error:(NSError**)error;

/// Acquire a license with a token.
///
/// - Parameters:
///   - token: PallyCon Token
///   - cid: Content ID
///   - siteID: Site ID
///   - userID: User ID
///   - acquisitionUrl: URL for License sever(default:PallyCon Server)
///   - isTemporary: Whether to store the license in the DB. If false, save the license.
///   - error: check error if nil no. succeeded if nil.
/// - Returns: TRUE if Succeeded, FALSE if Fail.
-(BOOL) acquireLicenseByToken:(NSString*)token cid:(NSString*)cid siteID:(NSString*)siteID userID:(NSString*)userID
               acquisitionUrl:(NSString*)acquisitionUrl isTemporary:(BOOL)isTemporary error:(NSError**)error;

/// It is returned by extracting information from the given token.
///
/// - Parameters:
///   - token: PallyCon Token
///   - error: check error if nil no. succeeded if nil.
/// - Returns : ``Ncg2TokenInfo``
-(Ncg2TokenInfo*) getTokenInfo:(NSString*)token error:(NSError**)error;




#pragma mark - Http Callback(Delegate)

/// Register NcgHttpRequestDelegate object on SDK.
/// It calls the method of relevant object when license sever and HTTP communication are needed inside SDK internally.
///
///  - Parameters:
///    - delegate :``NcgHttpRequestDelegate``
-(void) setHttpRequestDelegate:(id<NcgHttpRequestDelegate>) delegate;

#pragma mark - Exceptional Event Callback(Delegate)

///  Error event delegate that occurs within the SDK.
///  - Parameters:
///    - delegate : ``NcgExceptionalEventDelegate``
///    - logLevel : ``NCG_LOG_TYPE``
- (void) setExceptionalEventDelegate:(id<NcgExceptionalEventDelegate>) delegate logLevel:(LogType)type;

#pragma mark - License Information, Check And Acquisition


/// If the NCG content is licensed, you can check if it is valid.
/// @param path NCG Cotent Path.
/// @param lv out ``LicenseValidation``.
/// @param error check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note : NCG content can only be used with a valid license.
/// If use of NCG content is restricted, check the license with ``checkLicenseValidByPath:result:error:``.
/// If you use token, the ``checkLicenseValidByToken:result:error:`` function performs better.
-(BOOL) checkLicenseValidByPath:(NSString*)path result:(LicenseValidation*)lv error:(NSError**)error;


/// If the NCG content is licensed, you can check if it is valid.
/// @param cid  Content ID.
/// @param siteID  Site ID.
/// @param lv  out ``LicenseValidation``.
/// @param error  Check error if nil no. Succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note : NCG content can only be used with a valid license.
/// If use of NCG content is restricted, check the license with ``checkLicenseValidByCID:siteID:result:error:``.
/// If you use token, the ``checkLicenseValidByToken:result:error:`` function performs better.
-(BOOL) checkLicenseValidByCID:(NSString*)cid siteID:(NSString*)siteID result:(LicenseValidation*)lv error:(NSError**)error;



/// Check the license information saved as an NCG content file.
/// @param path  NCG content path.
/// @param lv out ``LicenseValidation``.
/// @param li out ``Ncg2LicenseInformation``.
/// @param error  Check error if nil no. Succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note: If you use token, the ``getLicenseInfoByToken:licenseValidation:licenseInformation:error:`` function performs better.
-(BOOL) getLicenseInfoByPath:(NSString*)path licenseValidation:(LicenseValidation*)lv licenseInformation:(Ncg2LicenseInformation**)li error:(NSError**)error;


/// Check the license information saved as an NCG content file.
/// @param cid  Content ID.
/// @param siteID  Site ID.
/// @param lv  out ``LicenseValidation``.
/// @param li  out ``Ncg2LicenseInformation``.
/// @param error  Check error if nil no. Succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note: If you use token, the ``getLicenseInfoByToken:licenseValidation:licenseInformation:error:`` function performs better.
-(BOOL) getLicenseInfoByCID:(NSString*)cid siteID:(NSString*)siteID licenseValidation:(LicenseValidation*)lv licenseInformation:(Ncg2LicenseInformation**)li error:(NSError**)error;


/// Check the license information saved as an NCG content file.
/// @param token t Token.
/// @param lv out ``LicenseValidation``.
/// @param li out ``Ncg2LicenseInformation``.
/// @param error   Check error if nil no. Succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
-(BOOL) getLicenseInfoByToken:(NSString*)token licenseValidation:(LicenseValidation*)lv licenseInformation:(Ncg2LicenseInformation**)li error:(NSError**)error;

/// It requests the license information of NCG file to license sever.
/// userID value is needed for user authentication on license server.
/// orderID value is necessary information to order and it is used only for a special cases. And it can be input null/(blank) value in general cases.
///
/// @param path	 	NCG file route and URL
/// @param userID 	User ID
/// @param orderID 	Order ID
/// @param isTemporary TRUE is stored in memory, false is stored in DB.
/// @param error Check error if nil no. Succeeded if nil.
/// ````
/// // Error Code
/// #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
/// // Error Message
/// #define NcgErrorKey_LicenseManagerErrorMsg      @"LicenseServerErrorMessage"
/// ```
/// @return TRUE if Succeeded, FALSE if Fail.
///
/// > Note: If you use token, the ``acquireLicenseByToken:isTemporary:error:`` function performs better.
-(BOOL) acquireLicenseByPath:(NSString*)path userID:(NSString*)userID orderID:(NSString*)orderID isTemporary:(BOOL)isTemporary error:(NSError**)error;


/**
 * It requests the license information of CID to license sever.
 * It can be used in case that there is no NCG file available and CID value is known for license acquisition.
 * For example, it can be used for playback of HLS contents.
 *
 * @param cid				Content ID
 * @param siteID			Site ID
 * @param userID			User ID
 * @param orderID			Order ID, it is able to transfer as empty value as an option.
 * @param acquisitionUrl	URL for License sever
 * @param isTemporary       TRUE is stored in memory, false is stored in DB.
 * @param error  Check error if nil no. Succeeded if nil.
 * ```
 * // Error Code
 * #define NcgErrorKey_LicenseManagerErrorCode     @"LicenseServerErrorCode"
 * // Error Message
 * #define NcgErrorK
 * ```
 * @return TRUE if Succeeded, FALSE if Fail.
 *
 * > Note: If you use token, the ``acquireLicenseByToken:isTemporary:error:`` function performs better.
 */
-(BOOL) acquireLicenseByCID:(NSString*)cid siteID:(NSString*)siteID userID:(NSString*)userID orderID:(NSString*)orderID
             acquisitionUrl:(NSString*)acquisitionUrl isTemporary:(BOOL)isTemporary error:(NSError**)error;

/// Will be deprecated.
///
/// - Parameters:
///   - path: NCG file route
///   - error: Check error if nil no. Succeeded if nil.
/// - Returns: TRUE if Succeeded, FALSE if Fail.
///
/// > Warning: **Will be deprecated**
- (BOOL) decreasePlaybackCount:(NSString*)path error:(NSError**)error DEPRECATED_MSG_ATTRIBUTE("deprecated");





#pragma mark - License Remove

/**
 * Remove a input license information of NCG file from lincese DB of device.
 *
 * @param path 		NCG file route
 * @param error   Check error if nil no. Succeeded if nil.
 * @return TRUE if Succeeded, FALSE if Fail.
 */
-(BOOL) removeLicenseByPath:(NSString*)path error:(NSError**)error;


/**
 * Removes contents license which are connected with NCG file.
 * The relevant file can not be used until acquiring the license again.
 *
 * @param cid       Contents ID
 * @param error Check error if nil no. Succeeded if nil.
 * @return TRUE if Succeeded, FALSE if Fail.
 */
-(BOOL) removeLicenseByCID:(NSString*)cid error:(NSError**)error;


/// Removes contents license which are connected with NCG file.
/// The relevant file can not be used until acquiring the license again.
/// @param cid  Contents ID.
/// @param siteID  Site ID.
/// @param error Check error if nil no. Succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
-(BOOL) removeLicenseByCID:(NSString*)cid siteID:(NSString*)siteID error:(NSError**)error;


/**
 * Delete the license stored in memory.
 *
 * @param error Check error if nil no. Succeeded if nil.
 * @return TRUE if Succeeded, FALSE if Fail.
 */
-(BOOL) removeAllTemporaryLicense:(NSError**)error;


#pragma mark - DRM File

/// Check if it is an NCG file.
/// @param path file path or URL.
/// @param error Check error if nil no. Succeeded if nil.
/// @return TRUE is NCG File. FALSE is plain file.
-(BOOL) isNcgContent:(NSString*)path error:(NSError**)error;

/**
 *  Create an ``Ncg2File`` object.  ``Ncg2File`` objects should be created through this method instead of creating the object directly.
 * @return Return ``Ncg2File`` instance
 */
-(Ncg2File*) createNcgFile:(NSError**)error;

#if TARGET_OS_SIMULATOR
#else
/// > Warning: **Deprecated**
    -(Ncg2FileZip*) createNcgFileZip:(NSError**)error DEPRECATED_MSG_ATTRIBUTE("deprecated");
#endif


/// Read and bring the Header information of NCG file.
///
/// @param path     NCG file's route
/// @param error Check error if nil no. Succeeded if nil.
/// @return ``Ncg2HeaderInformation`` object, nil if failed.
-(Ncg2HeaderInformation*) getNcg2HeaderInfo:(NSString*)path error:(NSError**)error;

#pragma mark - Secure Time

/// The DRM (Secure) time used inside the SDK is returned.
/// @return GMT Time.
-(NSString*) getNcgSecureTime;


/// If an error occurs that the Secure (DRM) Time is incorrect, call this method while connected to the Internet to update the time.
/// @param error Check error if nil no. Succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
/// > This function async.
-(BOOL) updateSecureTimeFromServer:(NSError**)error;

#pragma mark - Local web server

/// Obtain the created local web server instance.
/// @return Returns `Ncg2Webserver` object upon success
-(Ncg2Webserver*) getLocalWebServerInstance;


/// Returns the Device ID created by the SDK.
/// @param error Check error if nil no. Succeeded if nil.
/// @return Device ID string.
-(nullable NSString*) getNcgDeviceID:(NSError* _Nullable *_Nullable)error;


/// > Warning: **Will be deprecated**
-(NSString*) sendCustomRequest:(NSString*)acquisitionUrl siteID:(NSString*)siteID
                    requestData:(NSString*)requestData error:(NSError**)error DEPRECATED_MSG_ATTRIBUTE("Deprecated");

/// > Warning: **Will be deprecated**
-(NSString*) pallyconVendorRegistration:(NSString*)acquisitionUrl error:(NSError**)error DEPRECATED_MSG_ATTRIBUTE("Deprecated");

/// > Warning: **Will be deprecated**
-(void) enableLog DEPRECATED_MSG_ATTRIBUTE("Deprecated");

/// > Warning: **Will be deprecated**
-(void) disableLog DEPRECATED_MSG_ATTRIBUTE("Deprecated");

/// > Warning: **Will be deprecated**
-(void) setScreenRecorderAppDetecting:(BOOL)enabled DEPRECATED_MSG_ATTRIBUTE("Deprecated");

/// > Warning: **Will be deprecated**
-(NSString*) getDetectedScreenRecorderName DEPRECATED_MSG_ATTRIBUTE("Deprecated");


#pragma mark - HTTP Async Delegate
//-(int) onReceiveResponseHeader:(NSString*)header statusCode:(int)code statusMessage:(NSString*)message;
//-(int) onReceiveData:(NSData*)data dataLenght:(int)n;
//-(void) onFail:(NSString*)errorMessage;
//-(void) onComplete;


@end


