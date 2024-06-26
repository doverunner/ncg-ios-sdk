//
//  Ncg2File.h
//  MacNcgSDK
//
//  Created by JinyongPark on 2014. 11. 24..
//  Copyright (c) 2014년 INKAENTWORKS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Ncg2SdkCommon.h"


/// It seek ways which is used for seek method.
typedef enum _SeekMethod
{
    /// From the first position
    SM_Begin = 0,
    /// From current position
    SM_Current = 1,
    /// From the end
    SM_End = 2,
}SeekMethod;


/// This interface provides the interface which is able to decrypt the NCG file data.
/// It is provided by Ncg2Agent.createNcgFile method.
@interface Ncg2File : NSObject

/// DO NOT USE THIS METHOD.
/// Instead ``Ncg2Agent/createNcgFile:``
/// @param ncgCoreH  ncg core handle
/// @return ``Ncg2File`` instance
-(id) init:(void*) ncgCoreH;


/// Open NCG file
/// @param path NCG file path
/// @param isPrepare Whether to open the file in a decryptable state.
/// If TRUE, a license must be obtained and the license must be valid.
/// If FALSE, the license is not set in advance.
/// @param error check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
/// If FALSE, attempt to acquire a license``Ncg2Agent/acquireLicenseByToken:isTemporary:error:``.
-(BOOL) open:(NSString*)path isPrepare:(BOOL)isPrepare error:(NSError**)error;


/// In ``open:isPrepare:error:``, this function is called when ``isPrepare`` is TRUE.
/// If a license is saved, prepare to use a valid license.
/// @param error check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
/// If FALSE, attempt to acquire a license``Ncg2Agent/acquireLicenseByToken:isTemporary:error:``.
-(BOOL) prepare:(NSError**)error;


/// Releases resources allocated in the ``open:isPrepare:error:`` function.
-(void) close;


/// Read the NCG file to be used in the ``open:isPrepare:error:`` function.
/// @param buffer Buffer to store read data.
/// @param sizeToRead Data size to read.
/// @param error check error if nil no. succeeded if nil.
/// @return Size read.
-(int) read:(unsigned char*)buffer sizeToRead:(int)sizeToRead error:(NSError**)error;


/// Returns the current file pointer location.
/// @param error check error if nil no. succeeded if nil.
/// @return Current file pointer.
-(int64_t) getCurrentFilePointer:(NSError**)error;


/// Move the file pointer location.
/// @param offset Position to move to (offset)
/// @param method  Select ``SeekMethod``
/// ```
/// SM_Begin // From the first position
/// SM_Current // From current position
/// SM_End // From the end
/// ```
/// @param error check error if nil no. succeeded if nil.
/// @return TRUE if Succeeded, FALSE if Fail.
-(BOOL) seek:(int64_t)offset method:(SeekMethod)method error:(NSError**)error;


/// Returns the header information of the NCG file entered in ``open:isPrepare:error:``.
/// @param error check error if nil no. succeeded if nil.
/// @return ``Ncg2HeaderInformation``
-(Ncg2HeaderInformation*) getNcg2HeaderInfo:(NSError**)error;


/// Returns the size of the original file.
/// @param error check error if nil no. succeeded if nil.
/// @return Size of the original file.
-(int64_t) getContentSize:(NSError**)error;


/// Returns the NCG header size.
/// @param error check error if nil no. succeeded if nil.
-(int64_t) getNcgHeaderSize:(NSError**)error;


/// > Warning: **Will be deprecated**
-(BOOL) decreasePlayCount:(NSError**)error;

@end


