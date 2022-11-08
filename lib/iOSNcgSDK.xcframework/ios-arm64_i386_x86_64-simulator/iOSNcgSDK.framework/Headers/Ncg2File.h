//
//  Ncg2File.h
//  MacNcgSDK
//
//  Created by JinyongPark on 2014. 11. 24..
//  Copyright (c) 2014년 INKAENTWORKS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Ncg2SdkCommon.h"


/**
 * @if KOREA
 * seek 메소드에 사용되는 seek 방식을 표현한다.
 * @endif
 *
 * @if ENGLISH
 * It seek ways which is used for seek method.
 * @endif
 */
typedef enum _SeekMethod
{
    SM_Begin = 0,
    SM_Current = 1,
    SM_End = 2,
}SeekMethod;


/**
 * @if KOREA
 * 이 인터페이스는 NCG파일의 데이터를 복호화 인터페이스를 제공한다. <br>
 * Ncg2Agent.createNcgFile 메소드에 의해 생성되어진다.<br>
 * @endif
 *
 * @if ENGLISH
 * This interface provides the interface which is able to decrypt the NCG file data. <br>
 * It is provided by Ncg2Agent.createNcgFile method.<br>
 * @endif
 */
@interface Ncg2File : NSObject

/**
 * @if KOREA
 * DO NOT USE THIS METHOD.
 * It is only use for private.
 * @param ncgCoreH NCG Core Handle
 * @endif
 * @if ENGLISH
 * DO NOT USE THIS METHOD.
 * It is only use for private.
 * @param ncgCoreH NCG Core Handle
 * @endif
 */
-(id) init:(void*) ncgCoreH;

/**
 * @if KOREA
 * NCG 파일을 Open한다.<br>
 *
 * @param path       NCG 파일의 경로
 * @param isPrepare  복호화 가능상태로 파일을 오픈할 것인지의 여부. <br>
 * 만약 TRUE이면 라이선스가 존재해야 오류가 발생되지 않는다. 라이선스가 유효하지 않다면 오류가 발생된다.
 * @param error      오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공일 경우 YES, 실패는 NO 리턴한다.
 * @endif
 *
 * @if ENGLISH
 * It opens NCG file.<br>
 *
 * @param path	The route of NCG file.
 * @param isPrepare
 * @param error
 * @return
 * @endif
 */
-(BOOL) open:(NSString*)path isPrepare:(BOOL)isPrepare error:(NSError**)error;


/**
 * @if KOREA
 * 파일 [Ncg2File Open:] 시 isPrepare의 인자값이 YES일 경우 복호화 가능 상태가 되기 위한 처리를 수행한다.<br>
 *
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공일 경우 YES, 실패는 NO 리턴한다.
 * @endif
 *
 * @if ENGLISH
 * @param error
 * @endif
 */
-(BOOL) prepare:(NSError**)error;

/**
 * @if KOREA
 * open 및 prepare시에 할당된 자원일 해제하여 준다.
 * @return none.
 * @endif
 * @if ENGLISH
 *
 * @return none.
 * @endif
 */
-(void) close;

/**
 * @if KOREA
 * 파일로부터 데이터를 읽어들인다.
 * @param buffer        데이터를 읽어들일 버퍼.
 * @param sizeToRead   읽어들일 데이터의 사이즈
 * @param error         오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 읽은 사이즈를 리턴한다.
 * @endif
 * @if ENGLISH
 * @param buffer        buffer
 * @param sizeToRead   size
 * @param error         error
 * @return readed size
 * @endif
 */
-(int) read:(unsigned char*)buffer sizeToRead:(int)sizeToRead error:(NSError**)error;

/**
 * @if KOREA
 * 현재의 파일포인터 위치를 반환한다.
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 현재 파일포인터 위치
 * @endif
 * @if ENGLISH
 * @param error error
 * @return current file position
 * @endif
 */
-(int64_t) getCurrentFilePointer:(NSError**)error;


/**
 * @if KOREA
 * 읽어들일 파일포인터의 위치를 이동시킨다.
 *
 * @param offset	파일포인터의 위치를 이동시킬 offset를 해당 파라미터로 지정한다.
 * @param method    SeekMethod enum값 중 하나가 될 수 있다.<br>
 * Begin 은 0인덱스기반으로 파일포인터의 offset를 지정하는 것이고<br>
 * Current 는 현재의 파일포인터의 위치를 기반으로 offset을 지정하는 것이며<br>
 * End 는 끝 위치로 부터의 offset을 지정하는 것이다.<br>
 * 표준 C 함수의 fseek의 seek method사용방법과 동일하게 사용된다. <br>
 * @param error     오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공 시 YES, 실패 시 NO 리턴한다.
 * @endif
 *
 * @if ENGLISH
 * It moves file pointer location which is reading.
 *
 * @param offset	  It appoints offset which is moved the file pointer's location by parameter.
 * @param seekMethod  It could be one of SeekMethod enum values.<br>
 * Begin is to appoint offset of file pointer based on '0' zero index<br>
 * And Current is to appoint offset based on current file pointer's location.<br>
 * End is to appoint offset from the last position. <br>
 * It uses the same with how to use seek method of Standards C function's fseek. <br>
 * @param error error
 * @return YES if succeeded, NO if failed.
 * @endif
 */
-(BOOL) seek:(int64_t)offset method:(SeekMethod)method error:(NSError**)error;


/**
 * @if KOREA
 * NCG 파일의 헤더 정보 내용을 반환한다.<br>
 *
 * @param error 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return Ncg2HeaderInformation 객체를 반환한다. 만약 오류가 발생된 경우에는 nil로 반환된다.
 * @endif
 *
 * @if ENGLISH
 * Read and bring the Header information of NCG file.<br>
 *
 * @param  error
 * @return LicenseInfomation object if succeeded, An nil if failed.
 * @endif
 */
-(Ncg2HeaderInformation*) getNcg2HeaderInfo:(NSError**)error;

/**
 * @if KOREA
 * 원본 파일의 크기를 반환한다.
 * NCG 헤더의 크기를 제외한 원본파일의 크기를 확인할 때 사용할 수 있다.
 *
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 원본파일의 크기.
 * @endif
 * @if ENGLISH
 * @param error
 * @endif
 */
-(int64_t) getContentSize:(NSError**)error;

/**
 * @if KOREA
 * 횟수제한 컨텐츠인 경우 횟수를 차감할때 사용된다.
 *
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return 성공여부가 반환된다.
 * @endif
 * @if ENGLISH
 * @endif
 */
-(BOOL) decreasePlayCount:(NSError**)error;


/**
 * @if KOREA
 * NCG 헤더사이즈를 반환한다.
 *
 * @param error
 * 오류가 발생했을 경우 오류 정보를 자세히 확인하기 위해 error 객체를 전달할 수 있다. <br>
 * nil로 전달한 경우에는 오류가 발생했을 경우 자세한 내용을 알 수 없다.<br>
 * @return NCG 헤더사이즈
 * @endif
 * @if ENGLISH
 * @param error error
 * @return NCG Header size if succeeded.
 * @endif
 */
-(int64_t) getNcgHeaderSize:(NSError**)error;

@end


