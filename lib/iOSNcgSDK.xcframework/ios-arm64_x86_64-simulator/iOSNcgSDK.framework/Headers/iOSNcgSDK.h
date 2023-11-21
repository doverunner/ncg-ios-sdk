//
//  iOSNcgSDK.h
//  iOSNcgSDK
//
//  Created by yhpark on 04/10/2019.
//  Copyright © 2019 PallyCon. All rights reserved.
//

#import "Ncg2Agent.h"
#import "Ncg2File.h"
#if TARGET_OS_SIMULATOR
#else
    #import "Ncg2FileZip.h"
#endif
#import "Ncg2Webserver.h"
#import "Ncg2SdkCommon.h"
#import "NCG_Error.h"
