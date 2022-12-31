//
//  Ncg2FileZip.h
//  iOSNcgSDK
//
//  Created by yhpark on 2022/11/09.
//  Copyright © 2022 PallyCon. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Ncg2SdkCommon.h"


NS_ASSUME_NONNULL_BEGIN


/// This interface provides the interface which is able to decrypt the `NCG Zip` file data.
/// It is provided by `Ncg2Agent.createNcgZipFile` method.
///
/**
 * @if KOREA
 * NCG Zip 파일 복호화를 제공합니다.
 * Ncg2Agent.createNcgZipFile 함수로 객체를 생성해야 합니다.
 * @endif
 * @if ENGLISH
 * This interface provides the interface which is able to decrypt the `NCG Zip` file data.
 * It is provided by `Ncg2Agent.createNcgZipFile` method.
 * @endif
 */
@interface Ncg2FileZip : NSObject

/**
 * @if KOREA
 * 이 함수 대신 Ncg2Agent.createNcgZipFile 함수를 사용해야 합니다.
 * @param ncgHandle NCG Core 핸들
 * @return Ncg2FileZip 객체가 반환됩니다.
 * @endif
 * @if ENGLISH
 * DO NOT USE THIS METHOD.
 * Use this Ncg2Agent.createNcgZipFile instead.
 * @param ncgHandle NCG Core Handle
 * @return Ncg2FileZip instance
 * @endif
 */
-(id) init:(void*)ncgHandle;


/**
 * @if KOREA
 * zip이 복호화 할 준비합니다.
 * zip NCG 파일이 유효한지 유효한 라이선스가 있는 확인합니다.
 * @param zipPath `zip` file path(not URL).
 * @param error error retrun.
 * @return if `FALSE`, check the error.
 * @endif
 * @if ENGLISH
 * Prepare a `zip` file to decrypt.
 * Check that the zip `NCG` file is valid and has a valid license.
 * @param zipPath `zip` file path(not URL).
 * @param error error retrun.
 * @return if `FALSE`, check the error.
 * @endif
 */
-(BOOL) ncgZipPrepare:(nonnull NSString*)zipPath error:(NSError**)error;

/**
 * @if KOREA
 * Zip 파일 내 목록을 얻을 수 있습니다.
 * @return 문자열 배열을 반환합니다.
 * @endif
 * @if ENGLISH
 * Get a list of file in a `zip` file.
 * @return String array.
 * @endif
 */
-(NSArray<NSString*>*) ncgZipGetEntries;


/**
 * @if KOREA
 * 원하는 압축된 파일(Entry)을 오픈합니다.
 * @param entryName Entry name(path).
 * @param error error retrun.
 * @return if `FALSE`, check the error.
 * @endif
 * @if ENGLISH
 * Open the compressed file you want to use(Entry).
 * @param entryName Entry name(path).
 * @param error error retrun.
 * @return if `FALSE`, check the error.
 * @endif
 */
-(BOOL) ncgZipOpenEntry:(nonnull NSString*)entryName error:(NSError**)error;

/**
 * @if KOREA
 * 압축되어 암호화된 파일을 읽습니다.
 * @param buffer Read Buffer.
 * @param bufferSize Buffer Size.
 * @return Readed Size.
 * @endif
 * @if ENGLISH
 * Read compressed and encrypted files.
 * @param buffer Read Buffer.
 * @param bufferSize Buffer Size.
 * @return Readed Size.
 * @endif
 */
-(NSInteger) ncgZipRead:(char*)buffer bufferSize:(int)bufferSize;

/**
 * @if KOREA
 * Entry Seek.
 * @param offset Location to move.
 * @param method `SEEK_SET`, `SEEK_CUR`, `SEEK_END`.
 * @endif
 * @if ENGLISH
 * Entry Seek.
 * @param offset Location to move.
 * @param method `SEEK_SET`, `SEEK_CUR`, `SEEK_END`.
 * @endif
 */
-(void) ncgZipSeek:(NSInteger)offset method:(int)method;

/**
 * @if KOREA
 * `zip` End of File(EOF).
 * @return `true` is EOF, `false` otherwise,
 * @endif
 * @if ENGLISH
 * `zip` End of File(EOF).
 * @return `true` is EOF, `false` otherwise,
 * @endif
 */
-(BOOL) ncgZipEof;

/**
 * @if KOREA
 * Current location.
 * @return Location.
 * @endif
 * @if ENGLISH
 * Current location.
 * @return Location.
 * @endif
 */
-(NSInteger) ncgZipTell;


/**
 * @if KOREA
 * `zip` file close
 * @endif
 * @if ENGLISH
 * `zip` file close
 * @endif
 */
-(void) ncgZipClose;


/**
 * @if KOREA
 * 압축 파일 크기를 반환합니다.
 * @return File size.
 * @endif
 * @if ENGLISH
 * Compressed file size.
 * @return File size.
 * @endif
 */
-(NSInteger) ncgZipFileSize;

@end

NS_ASSUME_NONNULL_END
