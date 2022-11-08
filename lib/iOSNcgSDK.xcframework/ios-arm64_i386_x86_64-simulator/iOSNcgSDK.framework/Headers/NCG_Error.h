#ifndef    _NCG_ERROR_H
#define _NCG_ERROR_H

#ifdef  __cplusplus
extern "C" {
#endif

// 성공. 에러 없음.
#define    NCGERR_SUCCEED                    0x00000000  // 0

// 특별히 정의되지 않은 에러.
#define NCGERR_FAILED                    0xFFFFFFFF  // -1

#ifdef __APPLE__
// 이 버전의 SDK에서 제공되지 않는 API를 호출했음
#define NCGERR_NOT_AVAILABLE_API        0xF000F000  // -268374016
#endif


//////////////////////////////////////////////////////////////////////
// SDK 핸들 관련
//////////////////////////////////////////////////////////////////////
// NCG_Core_Handle가 입력되지 않았거나 NULL 인 경우
#define    NCGERR_INVALID_NCG_CORE_HANDLE        0xF0000101  // -268435199

// NCG_File_Handle가 입력되지 않았거나 NULL 인 경우
#define    NCGERR_INVALID_NCG_FILE_HANDLE        0xF0000102  // -268435198

// NCG_OIDs_Handle가 입력되지 않았거나 NULL 인 경우
#define    NCGERR_INVALID_NCG_OIDS_HANDLE        0xF0000103  // -268435197

// NCG_License_Handle가 입력되지 않았거나 NULL 인 경우
#define    NCGERR_INVALID_NCG_LICENSE_HANDLE    0xF0000104  // -268435196

// 패킷 스니핑이 감지된 경우
#define    NCGERR_LICENSE_DETECTION_SNIFFING    0xF0000105  // -268435195

// 루팅/탈옥 환경에서 재생이 허용되지 않은 컨텐츠의 라이센스 요청할때
#define    NCGERR_LICENSE_ABNORMAL_DEVICE        0xF0000106  // -268435194

#ifdef __APPLE__
// 네트워크가 연결되지 않은 상태에서 PD/HLS 컨텐츠의 재생을 요청할때
#define    NCGERR_NOT_CONNECTED_NETWORK        0xF0000107  // -268435193
#endif

//
#define    NCGERR_NETWORK_ERROR                0xF0000108  // -268435192

//
//    기기상태가 Offline으로 오래되어있어서 Offline지원모드이지만 온라인연결이 필요한 경우.
//
#define NCGERR_NEEDED_ONLINE_OFFLINE_TOO_LONG            0xF0000109

//
//    온라인 지원에서 기기는 Offline으로 되어있는 상태인 경우.
//
#define NCGERR_ONLY_SUPPORT_ONLINE_SUPPORT_MODE        0xF0000110

// NCG_Cenc_Decrypt_Handle가 입력되지 않았거나 NULL 인 경우
#define    NCGERR_INVALID_NCG_CENC_DECRYPT_HANDLE        0xF0000111  // -268435189

//////////////////////////////////////////////////////////////////////
// 시스템 정보 관련
//////////////////////////////////////////////////////////////////////
// 디바이스 ID가 입력되지 않은 경우.
// NULL로 끝나는 문자열이어야 한다.
#define    NCGERR_INVALID_DEVICE_ID        0xF0000201  // -268434943

// 디바이스 모델명이 입력되지 않은 경우.
// NULL로 끝나는 문자열이어야 한다.
#define    NCGERR_INVALID_DEVICE_MODEL        0xF0000202  // -268434942

#ifdef __APPLE__
// 디바이스가 정상 단말이 아닌 탈옥 단말인 경우.
// (AllowJB 계열 라이브러리를 사용할 경우 이 오류 코드는 발생하지 않음)
#define    NCGERR_INVALID_DEVICE_STATE        0xF0000203  // -268434941

// 디바이스에서 HTTP Daemon 프로세스가 시작되지 못했음
#define    NCGERR_HTTP_DAEMON_FAILED        0xF0000204  // -268434940
#endif
	
// 레지스트리로부터 디바이스 ID를 얻어오는데 실패한 경우.
#define	   NCGERR_GET_PCID			        0xF0000205  // -268434939


//////////////////////////////////////////////////////////////////////
// NCG 라이센스 요청-수신-업데이트 관련
//////////////////////////////////////////////////////////////////////
// 메세지를 받지 못함
#define    NCGERR_NO_RESPONSE                0xF0000301  // -268434687

// 잘못된 라이센스 요청 타입.
// 내부에서 발생한다.
#define    NCGERR_INVALID_REQUEST_TYPE        0xF0000302  // -268434686

// Session ID를 입력하지 않거나 잘못된 경우.
#define    NCGERR_INVALID_SESSION_ID        0xF0000303  // -268434685

// User ID를 입력하지 않거나 잘못된 경우.
#define    NCGERR_INVALID_USER_ID            0xF0000304  // -268434684

// Password를 입력하지 않았거나 잘못된 경우
#define    NCGERR_INVALID_PASSWORD            0xF0000305  // -268434683

// Content ID를 입력하지 않았거나,
// NCG 파일 내의 CID가 손상되었거나 가져오지 못함.
#define    NCGERR_INVALID_CONTENT_ID        0xF0000306  // -268434682

// Side ID를 입력하지 않았거나,
// NCG 파일 내의 SID가 손상되었거나 가져오지 못함.
#define    NCGERR_INVALID_SITE_ID            0xF0000307  // -268434681

// Reserved.
#define NCGERR_INVALID_GROUP_ID            0xF0000308  // -268434680

// 서버에 전송할 클라이언트 Diffie-Hellman 키 생성 실패
#define    NCGERR_GENERATE_DH_KEY_FAIL        0xF0000309  // -268434679

// 수신한 메시지가 xml 형식이 아님.
#define    NCGERR_INVALID_XML_RESPONSE        0xF000030A  // -268434678


//////////////////////////////////////////////////////////////////////
// 서버로 부터 수신한 메시지가 RO (Right Object, License)인 경우
// RO 메세지의 형식이 올바르지 않음.
// XML 문자열 자체가 손상되었거나,
// 반드시 필요한 필드가 없는 경우이다.
#define    NCGERR_INVALID_RO_RESPONSE        0xF0000321  // -268434655

// RO 메세지가 손상됨. (= 해시 검증 실패)
#define    NCGERR_INVALID_RO_RESPONSE_HASH    0xF0000322  // -268434654

// RO 메세지에 포함된 Diffie-Hellman 값 가져오기 실패.
#define    NCGERR_INVALID_RO_RESPONSE_B    0xF0000323  // -268434653

// 클라이언트 Diffie-Hellman 값이 존재하지 않았는데 서버로부터 값 받음.
// 라이센스 요청 메시지 생성 단계에 오류가 있었는데 무시하고 요청한 경우
// 요청 - 응답처리 짝을 맞추지 않은 경우에 발생한다.
// 동시에 여러 요청과 응답을 처리할 수 없다.
// 반드시 요청-처리, 요청-처리를 1:1로 처리해야 한다.
#define    NCGERR_NO_CLIENT_DH_KEY            0xF0000324  // -268434652

// RO에 포함된 라이센스 형식 (XML) 오류.
#define    NCGERR_INVALID_LICENSE            0xF0000325  // -268434651

// RO에 포함된 라이센스 타입 오류.
// RO에 <cid> 혹은 <sid> 중 하나가 반드시 포함되어야 한다.
#define    NCGERR_INVALID_LICENSE_TYPE        0xF0000326  // -268434650

// RO에 <cid> 가 포함되어 있으나 잘못된 라이센스.
// <cid> RO XML 파싱에 실패한 경우이다.
#define    NCGERR_INVALID_CID_LICENSE_XML    0xF0000327  // -268434649

// RO에 <sid> 가 포함되어 있으나 잘못된 라이센스.
// <sid> RO XML 파싱에 실패한 경우이다.
#define    NCGERR_INVALID_SID_LICENSE_XML    0xF0000328  // -268434648

// cid/sid RO에 포함된 <permission> XML 오류.
#define    NCGERR_INVALID_PERMISSION_XML    0xF0000329  // -268434647

// RO는 정상이나 기기에 정보 업데이트 실패.
#define    NCGERR_UPDATE_LICENSE_FAIL        0xF000032A  // -268434646

#ifdef __APPLE__
// 서버로부터 수신한 메시지에 오류 정보가 포함되어 있음.
#define NCGERR_LICENSE_SERVER_MESSAGE    0xF000032B  // -268434645
#endif

// NCG 권한 시작 시간 오류.
#define NCGERR_INVALID_START_DATE        0xF0000331  // -268434639

// NCG 권한 만기 시간 오류.
#define NCGERR_INVALID_END_DATE            0xF0000332  // -268434638


//////////////////////////////////////////////////////////////////////
// 서버로 부터 수신한 메시지가 구매 URL 혹은 주문 ID 목록인 경우
// 수신한 메시지 안에 OID가 더이상 없음.
// 에러는 아닌 일반적인 상황이며, 내부에서 발생한다.
#define    NCGERR_INVALID_OID_LIST            0xF0000331  // -268434639

// 함수 호출시 입력한 주문 ID 인덱스가 범위를 벗어남.
// 0보다 작거나, 서버로부터 받은 주문 ID 갯수를 초과한 경우.
#define NCGERR_ORDERID_INDEX_OVERFLOW    0xF0000332  // -268434638

// 구매 URL XML이 잘못됨.
#define NCGERR_INVALID_PURCHASE_URL        0xF0000333  // -268434637


//////////////////////////////////////////////////////////////////////
// NCG 라이센스 보관소 관련
//////////////////////////////////////////////////////////////////////

// 입력받은 DB 경로가 너무 김.
// 경로길이가 230 이하여야 함
#define    NCGERR_TOO_LONG_LICENSE_DB_PATH    0xF0000401  // -268434431
#ifndef NCGERR_TOO_LONG_LICENSE_DB_PATH
#define    NCGERR_TOO_LONG_LICENSE_DB_PATH    0xF0000401  // -268434431
#endif

// 저장된 비밀값이 일치하지 않음.
// 라이센스 파일 백업본이 존재할 가능성이 있음.
// 횟수제를 사용할 때에 보안을 위해서 필요하다.
#define NCGERR_RANDOM_SECRET_MISMATCH    0xF0000402  // -268434430

// 올바르지 않은 CID / SID 타입
// 관련 함수 호출 시
// NCG_CID_TYPE 혹은 NCG_SID_TYPE이 사용되어야 한다.
#define NCGERR_INVALID_ID_TYPE            0xF0000403  // -268434429

// CID DB 열기 실패
#define NCGERR_CID_DB_OPEN_FAIL            0xF0000411  // -268434415

// CID DB 읽기 실패
#define NCGERR_CID_DB_READ_FAIL            0xF0000412  // -268434414

// CID DB 쓰기 실패
#define NCGERR_CID_DB_WRITE_FAIL        0xF0000413  // -268434413

// CID DB 삭제 실패
#define    NCGERR_CID_DB_DELETE_FAIL        0xF0000414  // -268434412

// 현 SDK 버전에서 지원할 수 없는 CID DB 버전
#define NCGERR_NOT_SUPPORTED_CID_DB_VER    0xF0000415  // -268434411

// CID 라이센스가 전혀 없거나 로드되지 않은 상태에서 삭제/Trim 시도
#define    NCGERR_NO_CID_LICENSE            0xF0000416  // -268434410

// RODB 마이그레이션 중단
#define    NCGERR_STOP_MIGRATION            0xF0000417  // -268434409

// 해당하는 CID의 라이선스 찾을 수 없음
#define    NCGERR_NO_LICENSE_BY_CID         0xF0000418  // -268434408

// SID DB 열기 실패
#define NCGERR_SID_DB_OPEN_FAIL            0xF0000421  // -268434399

// SID DB 읽기 실패
#define NCGERR_SID_DB_READ_FAIL            0xF0000422  // -268434398

// SID DB 쓰기 실패
#define NCGERR_SID_DB_WRITE_FAIL        0xF0000423  // -268434397

// SID DB 삭제 실패
#define    NCGERR_SID_DB_DELETE_FAIL        0xF0000424  // -268434396

// 현 SDK 버전에서 지원할 수 없는 SID DB 버전
#define NCGERR_NOT_SUPPORTED_SID_DB_VER    0xF0000425  // -268434395

// SID 라이센스가 전혀 없거나 로드되지 않은 상태에서 삭제/Trim 시도
#define    NCGERR_NO_SID_LICENSE            0xF0000426  // -268434394

// DB 덤프 파일 생성 실패
#define    NCGERR_DUMP_CREATE_FAIL            0xF0000431  // -268434383

// 기기에 저장된 시간이 없음
#define NCGERR_NO_TIME_FILE                0xF0000441  // -268434367

// 시간 저장 파일 열기 실패
#define NCGERR_TIME_FILE_OPEN_FAIL        0xF0000442  // -268434366

// 시간 저장 파일 읽기 실패
#define NCGERR_TIME_FILE_READ_FAIL        0xF0000443  // -268434365

// 시간 저장 파일 쓰기 실패
#define NCGERR_TIME_FILE_WRITE_FAIL        0xF0000444  // -268434364

// 시간 저장 파일의 ID가 일치하지 않음
#define NCGERR_TIME_FILE_ID_MISMATCH    0xF0000445  // -268434363

// 저장된 시간보다 이전 시간이 입력됨
// 시간이 바뀌었을 가능성이 있음
#define NCGERR_CORRUPT_DEVICE_TIME        0xF0000446  // -268434362

// 파일 핸들/디스크립터가 비정상
#define    NCGERR_INVALID_FILE_POINTER        0xF0000451  // -268434351
#ifndef NCGERR_INVALID_FILE_POINTER
#define    NCGERR_INVALID_FILE_POINTER        0xF0000451  // -268434351
#endif
#define    NCGERR_GET_DBFILE_FD_FAIL        0xF0000452  // -268434350

// DB 파일 정보를 가져올 수 없음
#define    NCGERR_GET_DBFILE_INFO_FAIL        0xF0000453  // -268434349

// DB 파일이 외부에서 변경됨
#define NCGERR_MODIFIED_DBFILE_INO        0xF0000461  // -268434335
#define NCGERR_MODIFIED_DBFILE_MTIME    0xF0000462  // -268434334
#define NCGERR_MODIFIED_DBFILE_HASH        0xF0000463  // -268434333

// RODBv2의 저장된 CID 구조체에 해당되는 데이터가 깨진 경우
// 해당 경우는 DB에 사용되는 구조체가 적절히 패치되지 못한 버그이다. 이를 해결하기 위해 내부적으로 사용되는 해당 오류코드가 추가되었다.
#define NCGERR_CORRUPT_RODB_V2_ENTRY    0xF0000464  // -268434332


//
// RODB 파일이 유효하지 않은 경우, DeviceID가 RODB생성시와 달라졌을때 발생될 수 있다.
//
#define NCGERR_CORRUPT_RODB             0xF0000465  // -268434331


// RODB(SQLite) 관련 오류
#define NCGERR_RODB_FAILED              0xF0000466

// RODB(SQLite) 데이터 레코드가 없는 경우.
#define NCGERR_RODB_NOT_FOUND            0xF0000467


//////////////////////////////////////////////////////////////////////
// NCG 컨텐츠 관련
//////////////////////////////////////////////////////////////////////
// NCG 헤더가 존재하지 않거나 손상.
// NCG 파일이 아닐 수 있다.
#define    NCGERR_INVALID_NCG_HEADER        0xF0000501  // -268434175

// NCG 헤더가 손상 (= 해시 검증 실패).
#define NCGERR_MODIFIED_NCG_HEADER        0xF0000502  // -268434174

// NCG 헤더에 포함된 XML에 오류가 있음.
#define    NCGERR_INVALID_NCG_XML_HEADER    0xF0000503  // -268434173

// NCG 헤더 길이가 더 필요함.
// 함수 설명에 따라 필요한 버퍼를 읽어들인 후 다시 호출한다.
#define NCGERR_NEEDED_MORE_HEADER_DATA    0xF0000504  // -268434172

// NCG_Open() 시에 파일을 직접 열도록 지정하지 않고
// NCG_Read(), NCG_Seek() 등을 호출할 때 발생한다.
#define NCGERR_NOT_ALLOWED_CALL            0xF0000511  // -268434159

// NCG 파일 열기 실패.
// 파일 존재하지 않음, 디렉토리 접근 권한 없음,
// 시스템 문자열 인코딩으로 인해 찾을 수 없는 경우에 발생한다.
#define    NCGERR_FILE_OPEN_FAIL            0xF0000512  // -268434158

// NCG 파일 포인터 이동 실패.
#define NCGERR_FILE_SEEK_FAIL            0xF0000513  // -268434157

// NCG 파일헤더를 검사하기 위해 파일을 읽었을때 헤더크기만큼 read가 안된 경우.
#define NCGERR_TOO_SMALL_FILE_TO_CHECK_HEADER    0xF0000514  // -268434156


#ifdef __APPLE__
// 이전 컨텐츠 재생 소켓이 아직 종료되지 않아 재생을 시작하지 못함, 재시도 필요
#define    NCGERR_CANNOT_START_PLAY_VIDEO_NOW    0xF0000515  // -268434155
#endif


//////////////////////////////////////////////////////////////////////
// NCG 컨텐츠 - 라이센스 관련
//////////////////////////////////////////////////////////////////////
// 기기에 저장된 라이센스가 없음.
// 즉, 어떠한 NCG 파일도 열 수 없음
// NOTE:
// 해당 오류코드는 다음 오류코드로 대체됨. => NCGERR_NO_CID_LICENSE 로 대체시킴. added by jypark.
// (동일한 용도로 사용되므로 하나의 오류코드로 통일시키기 위함.)
//#define    NCGERR_NO_LICENSES_IN_DEVICE    0xF0000601  // -268433919

// NCG 파일을 열기 위한 라이센스(CID)가 없음.
// CID 라이센스는 반드시 필요하며,
// SID 라이센스는 추가적으로 있을 수도, 없을 수도 있다.
// must required
// NOTE:
// 해당 오류코드는 다음 오류코드로 대체됨. => NCGERR_NO_CID_LICENSE 로 대체시킴. added by jypark.
// (동일한 용도로 사용되므로 하나의 오류코드로 통일시키기 위함.)
//#define    NCGERR_NO_LICENSE_FOR_FILE        0xF0000602   // -268433918


// 함수 호출시 입력한 라이센스 인덱스가 범위를 벗어남.
// 0보다 작거나, 라이센스 핸들이 가진 라이센스 갯수를 초과한 경우.
#define NCGERR_LICENSE_INDEX_OVERFLOW    0xF0000603   // -268433917

// 재생 횟수가 무제한인 컨텐츠에 대한 재생 횟수 차감 시도
#define NCGERR_UNLIMITED_PLAYCOUNT        0xF0000604   // -268433916

// 재생시간을 비교할 문자열, 즉 현재 시간이 올바른 GMT 포멧이 아님.
// 반드시 2010-01-01T12:34:56Z 형태이어야 한다.
#define NCGERR_INVALID_GMT_FORMAT        0xF0000605   // -268433915

// 현재 시간이 잘못된 값이 입력됨.
#define NCGERR_INVALID_CURRENT_GMT        0xF0000606   // -268433914

// NCG 파일을 복호화할 권한이 지정되지 않은 상태에서 복호 시도.
// 라이센스 설정( NCG_SetLicense() )에서 실패했음에도 복호 시도 했을 때 등.
#define NCGERR_NO_PERMISSION_FOR_FILE    0xF0000607   // -268433913

// GMT 시간이 2000년 이전.
// 2000년 1월 1일 0시 이후 시간만 사용 가능하다
#define NCGERR_TO_SMALL_GMT                0xF0000608   // -268433912
#ifndef NCGERR_TO_SMALL_GMT
#define NCGERR_TO_SMALL_GMT                0xF0000608   // -268433912
#endif

// NCG 파일을 열 수 있는 기간 이전.
#define NCGERR_BEFORE_START_DATE        0xF0000611   // -268433903

// NCG 파일을 열 수 있는 기간 이후. 즉 만료.
#define NCGERR_AFTER_END_DATE            0xF0000612   // -268433902

// 재생 횟수가 만기된 컨텐츠에 대한 재생 횟수 차감 시도
// 혹은 재생시도할 때 재생 횟수 만료
#define NCGERR_PLAYCOUNT_EXHAUSTION        0xF0000613   // -268433901

// 라이센스 DB에서 CID 삭제 실패. 해당 CID가 없는 경우이다.
#define    NCGERR_CID_LICENSE_REMOVE_FAIL    0xF0000621   // -268433887

// 라이센스 DB에서 SID 삭제 실패. 해당 SID가 없는 경우이다.
#define    NCGERR_SID_LICENSE_REMOVE_FAIL    0xF0000622   // -268433886

#ifdef __APPLE__
// 등록되지 않은 기기에서의 RO 요청.
#define NCGERR_UNREGISTERED_DEVICE        0xF0000623   // -268433885

// 유효한 구매정보 또는 권한정보를 찾을 수 없음.
#define NCGERR_PURCHASE_RIGHTS_UNKNOWN    0xF0000624   // -268433884

// 이미 도메인에 등록된 기기에서 Join 요청
#define NCGERR_DEVICE_ALREADY_JOINED    0xF0000625   // -268433883

// 도메인에 등록되지 않은 기기에서 Leave 요청
#define NCGERR_DEVICE_NOT_JOINED        0xF0000626   // -268433882

// 도메인에 등록 허용된 기기 대수가 초과되었음
#define NCGERR_DEVICE_DOMAIN_EXCEEDED    0xF0000627   // -268433881

// 외부 디스플레이가 연결된 상태에서 외부 출력이 제한된 컨텐츠를 재생 시도함
#define NCGERR_EXTERNAL_OUTPUT_FAILED    0xF0000628   // -268433880
#endif

// 라이센스 핸들을 요청했으나, 파일이 평문일 때
// NCG_SetLicense() 나 NCG_SetCEKForce() 없이 read 를 할 수 있다.
#define    NCGERR_PLAIN_FILE                0xF0000631   // -268433871

// PKI 연산중 오류가 발생된 경우
#define    NCGERR_PKI_CRYPTO_ERROR            0xF0000632   // -268433870


// 디바이스시간이 변경되었음을 감지한 경우.
#define    NCGERR_DETECTED_DEVICE_TIME_MODIFIED                        0xF0000701

// 허용되지 않은 appid인 경우.
#define    NCGERR_NOT_AUTHORIZED_APPID                                    0xF0000702

// SecureTime이 기록되는 파일이 삭제된 경우.
#define    NCGERR_SECURETIEM_FILE_NOT_FOUND                            0xF0000703

//////////////////////////////////////////////////////////////////////
// NCG 기타 에러
//////////////////////////////////////////////////////////////////////
// 메모리 할당 실패.
#define    NCGERR_MEMOEY_ALLOCATION_FAIL    0xF0001001   // -268431359

// 함수 입력 파라미터가 올바르지 않은 경우.
// OPTIONAL이 아닌 필요한 변수에 NULL 이 입력될 때 주로 발생.
#define NCGERR_INVALID_PARAMETER        0xF0001002   // -268431358

// BASE64 인코딩 실패.
// 라이센스 요청시 사용된다.
#define    NCGERR_BASE64ENCODE                0xF0001011   // -268431343

// BASE64 디코딩 실패.
// 라이센스 수신시 사용된다.
#define    NCGERR_BASE64DECODE                0xF0001012   // -268431342

// URL 인코딩 실패.
// 라이센스 요청시 사용된다.
#define    NCGERR_URLENCODE                0xF0001013   // -268431341

// 라이센스를 요청할 수 없는 Content Type으로
// 라이센스 요청시 발생.
#define    NCGERR_CANNOT_REQUEST_RO_CONTENT_TYPE    0xF0001014   // -268431340


// CEK 복호화 실패
#define    NCGERR_CEK_DECRYPTION_ERROR                    0xF0001015

// PKI 통신 실패 : 인증서 다운로드
//
#define    NCGERR_FAILED_TO_DOWNLOAD_CERTIFICATE        0xF0002000   // -268427264

// PKI 통신 실패 : 라이센스 다운로드
//
#define    NCGERR_FAILED_TO_DOWNLOAD_LICENSE            0xF0002001   // -268427263


// PKI 통신 실패 : 라이센스에서 명시적으로 오류를 Response 시킴.
// 서버가 Response시에 Secure Channel에 Response XML에 명시적인 오류코드를 명시한 경우 해당 오류가 반환된다.
// 타임아웃이나 페이지NotFound등의 HTTP 통신오류가 아닌 기기횟수초과, 권한등의 이유로 실패하는 경우에 해당 오류코드가 반환된다.
//
#define    NCGERR_LICENSE_SERVER_RESPONSE_ERROR        0xF0002003   // -268427261


// PKI 통신 실패 : 라이센스에서 명시적으로 오류를 Response 시킴.
// 서버가 Response시에 Secure Channel에 Response XML에 명시적인 오류코드를 명시한 경우 해당 오류가 반환된다.
// 타임아웃이나 페이지NotFound등의 HTTP 통신오류가 아닌 기기횟수초과, 권한등의 이유로 실패하는 경우에 해당 오류코드가 반환된다.
//
#define    NCGERR_PKI_NOT_SUPPORTED_ERROR                0xF0002004   // -268427260

//
#define NCGERR_FAILED_TO_GET_SECURETIME                0xF0002005   // -268427259
#define NCGERR_FAILED_TO_SEND_CUSTOM_REQUEST        0xF0002006   // -268427258

#define NCGERR_UNSUPPORTED_OPERATION                0xF0002007   // -268427257


#define NCGERR_FAILED_HASH_CHECK                    0xF0002008   // -268427256


#define    NCGERR_FAILED_TO_GET_SECURE_CLOCK            0xF0002009   // -268427255

#define    NCGERR_NOT_PREPARED_STATE                    0xF0002010


// 디바이스에서 라이선스를 요청하기 위해 저장된 인증서로 암호화하여 서버에 보내고 서버는 요청 정보의 디바이스 인증서를 DB에서 찾아
// 복호화를 시도하는데 이를 실패하는 경우 7003 오류를 리턴하게 된다.
// 원인은 알수 없는 이유로 디바이스 또는 서버에 저장된 인증서에 오류가 있거나, 서버에 UserID + DeviceID 쌍에 맞는 인증서가 없을때이다.
// 즉, 단말에서 보내준 인증서와 서버에 저장된 디바이스 인증서가 다를때이다.
// 이 경우 NCG Core에서 저장된 인증서를 삭제하고, 다음 라이선스 요청 시 새로운 디바이스 인증서를 서버로 보낸다.
#define    NCGERR_LICENSE_SERVER_RESPONSE_CERTIFICATE_ERROR  7003


#define NCGERR_FAILED_TO_INIT_ARCHIVE_CONTEXT        0xF0003000


#define    NCGERR_CANNOT_START_LOCALWEBSERVER            0xF0004000

// Duration After Use 컨텐츠를 처음으로 재생한 경우에 _ncg_CheckValidate 함수에서 반환할 수 있다.
#define NCGERR_PLAY_FIRST_DURATION_AFTER_USE        0x01000001   // 16777217

// Player status check
enum {
    NCGPlayerStatusUnknown = 0x0020,
    NCGPlayerStatusReadyToPlay,
    NCGPlayerStatusFailed
};

// 오류 체크용 매크로
#define Succeed(x)    (x)    == NCGERR_SUCCEED
#define    Failed(x)    (x) != NCGERR_SUCCEED

#ifdef  __cplusplus
}
#endif

#endif    // _NCG_ERROR_H

