//
//  YPMacros.h
//  YPMacros
//
//  Created by mac on 2021/9/23.
//  Copyright © 2021 yaodunpeng. All rights reserved.
//

#ifndef YPMacros_h
#define YPMacros_h

#pragma mark --
#pragma mark -- 打印设置
/**
 调试
 **/
#ifdef DEBUG
#define ALog(fmt, ...) NSLog(fmt, ##__VA_ARGS__)
//DEBUG  模式下打印日志,当前行
# define DLog(fmt, ...) NSLog((@"[Class:%s]\n" "[Methed:%s]\n" "[Line:%d] \n" fmt), __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define ALog(fmt, ...)
#define DLog(fmt, ...)
#define NSLog(...) {}
#endif

#pragma mark --
#pragma mark -- 设备、界面
#define kScreenWidth  [[UIScreen mainScreen] bounds].size.width
#define kScreenHeight [[UIScreen mainScreen] bounds].size.height

/** NavigationBar 高度：44 */
#define kNavigationBarH         44.0f
/** 状态栏 加 NavigationBar 高度 iPhoneX：88 other：64  */
#define kStatusAndNavBarH       (kStatusBarH + kNavigationBarH)

/** HomeLineH 高度 iPhoneX:34 other:0 */
#define kHomeLineH              (isIphoneX ? 34.0f : 0.0f)
/** TabBar 高度 iPhoneX:83 other:49 */
#define kTabBarH                (49.0 + kHomeLineH)

/** Tabbar 隐藏状态下 头尾高度 iPhoneX:171 other:113 */
#define kNavHAndTabBarHiddenH    (kStatusAndNavBarH + kHomeLineH)
/** Tabbar 显示状态下 头尾高度 iPhoneX:122 other:64 */
#define kNavHAndTabBarShowH      (kStatusAndNavBarH + kTabBarH)

/** 状态栏高度 - 自动判断是否 iPhoneX */
#define kStatusBarH \
({float statusBarHeight = 0;\
if ([[UIApplication sharedApplication] isStatusBarHidden]) {\
if (@available(iOS 13.0, *)) {\
UIStatusBarManager *statusBarManager = [UIApplication sharedApplication].windows.firstObject.windowScene.statusBarManager;\
statusBarHeight = statusBarManager.statusBarFrame.size.height;\
statusBarHeight = statusBarHeight == 0 ? [[UIApplication sharedApplication] delegate].window.safeAreaInsets.top : statusBarHeight;\
}\
statusBarHeight = statusBarHeight == 0 ? (isIphoneX ? 44.0f : 20.0f) : statusBarHeight;\
} else {\
if (@available(iOS 13.0, *)) {\
UIStatusBarManager *statusBarManager = [UIApplication sharedApplication].windows.firstObject.windowScene.statusBarManager;\
statusBarHeight = statusBarManager.statusBarFrame.size.height;\
if (statusBarHeight == 0) {\
statusBarHeight = [[UIApplication sharedApplication] delegate].window.safeAreaInsets.top;\
}\
} else {\
statusBarHeight = [UIApplication sharedApplication].statusBarFrame.size.height;\
}\
}\
(statusBarHeight);})


/** 是否是 iPhone X 系列 */
#define isIphoneX \
({BOOL isPhoneX = NO;\
if (IS_IPHONE) {\
if (@available(iOS 11.0, *)) {\
isPhoneX = [[UIApplication sharedApplication] delegate].window.safeAreaInsets.bottom > 0.0;\
} else {\
isPhoneX = NO;\
}\
} else {\
isPhoneX = NO;\
}\
(isPhoneX);})

#define SCREEN_MAX_LENGTH (MAX(kScreenWidth, kScreenHeight))
#define SCREEN_MIN_LENGTH (MIN(kScreenWidth, kScreenHeight))

#define IS_IPHONE_4_OR_LESS (IS_IPHONE && SCREEN_MAX_LENGTH < 568.0)
#define IS_IPHONE_5         (IS_IPHONE && SCREEN_MAX_LENGTH == 568.0)
#define IS_IPHONE_6         (IS_IPHONE && SCREEN_MAX_LENGTH == 667.0)
#define IS_IPHONE_6P        (IS_IPHONE && SCREEN_MAX_LENGTH == 736.0)
#define IS_IPHONE_7         (IS_IPHONE && SCREEN_MAX_LENGTH == 667.0)
#define IS_IPHONE_7P        (IS_IPHONE && SCREEN_MAX_LENGTH == 736.0)
#define IS_IPHONE_8         (IS_IPHONE && SCREEN_MAX_LENGTH == 667.0)
#define IS_IPHONE_8P        (IS_IPHONE && SCREEN_MAX_LENGTH == 736.0)
#define IS_IPHONE_X         (IS_IPHONE && SCREEN_MAX_LENGTH == 812.0)

#define kIPHONE_7W 375.0
#define kIPHONE_7H 667.0


#pragma mark -- 大小判断
#define MAX(a, b)           a > b ? a : b
#define MIN(a, b)           a < b ? a : b


#pragma mark -- 设置 View 圆角 和 边框
#define LayerBorderRadius(View, Radius, Width, Color)\
\
[View.layer setCornerRadius:(Radius)];\
[View.layer setBorderWidth:(Width)];\
[View.layer setBorderColor:[Color CGColor]];\
[View.layer setMasksToBounds:YES] // view圆角


#pragma mark -- View 圆角
#define ViewRadius(View, Radius)\
\
[View.layer setCornerRadius:(Radius)];\
[View.layer setMasksToBounds:YES]


#pragma mark --
#pragma mark -- 是否iPad、iPhone
#define IS_IPAD     (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
#define IS_IPHONE   (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)

#pragma mark --
#pragma mark -- 单例设置

#define KSingleToolH(name) + (instancetype)share##name;

// .m文件
#define KSingleToolM(name) \
static id _instance; \
\
+ (instancetype)allocWithZone:(struct _NSZone *)zone \
{ \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
_instance = [super allocWithZone:zone]; \
}); \
return _instance; \
} \
\
+ (instancetype)share##name \
{ \
static dispatch_once_t onceToken; \
dispatch_once(&onceToken, ^{ \
_instance = [[self alloc] init]; \
}); \
return _instance; \
} \
\
- (id)copyWithZone:(NSZone *)zone \
{ \
return _instance; \
}

#pragma mark --
#pragma mark -- 版本比较
/** 当前版本 */
#define kSystemVersion           ([[UIDevice currentDevice] systemVersion])
#define kSystemVersionF          ([[[UIDevice currentDevice] systemVersion] floatValue])
#define kSystemVersionD          ([[[UIDevice currentDevice] systemVersion] doubleValue])

//检查系统版本
#define SYSTEM_VERSION_EQUAL_TO(v)                  ([kSystemVersion compare:v options:NSNumericSearch] == NSOrderedSame)
#define SYSTEM_VERSION_GREATER_THAN(v)              ([kSystemVersion compare:v options:NSNumericSearch] == NSOrderedDescending)
#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([kSystemVersion compare:v options:NSNumericSearch] != NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN(v)                 ([kSystemVersion compare:v options:NSNumericSearch] == NSOrderedAscending)
#define SYSTEM_VERSION_LESS_THAN_OR_EQUAL_TO(v)     ([kSystemVersion compare:v options:NSNumericSearch] != NSOrderedDescending)

/* 是否大于等于IOS7 */
#define isIOS7              (kSystemVersionF >= 7.0)
/* 是否大于等于IOS8 */
#define isIOS8              (kSystemVersionF >= 8.0)
/* 是否大于IOS9 */
#define isIOS9              (kSystemVersionF >= 9.0)
/* 是否大于等于某个版本 */
#define isIOS(version)      (kSystemVersionF >= (version))


#pragma mark --
#pragma mark --  文件目录
/** 获取temp */
#define kPathTemp       NSTemporaryDirectory()
/** Document 沙河路径 */
#define kPathDocument   [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0]
/** Cache 沙河路径 */
#define kPathCache      [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) objectAtIndex:0]

#pragma mark --
#pragma mark --  常见主要单例
#define kApplication        [UIApplication sharedApplication]
#define kAppDelegate        [[UIApplication sharedApplication] delegate]
#define kKeyWindow          [UIApplication sharedApplication].keyWindow
#define kUserDefaults       [NSUserDefaults standardUserDefaults]



//时间戳
#define kCurrentTime        [NSString stringWithFormat:@"%ld", (long)[[NSDate date] timeIntervalSince1970]]

//获取当前语言
#define kCurrentLanguage    ([[NSLocale preferredLanguages] objectAtIndex:0])
//多语言
#define   kLocStr(str)      NSLocalizedString(str, nil)

// 检查字符串是否为空(PS：这里认为nil," ", "\n"均是空)
#define strIsEmpty(str)     (str==nil || [str length]==0 || [[str stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]] length] == 0)



#pragma mark -
#pragma mark NSNumber
/** int 转 NSNumber */
#define kNUMBER_INT(intValue)           [NSNumber numberWithInt:intValue]
/** float 转 NSNumber */
#define kNUMBER_FLOAT(floatValue)       [NSNumber numberWithFloat:floatValue]
/** double 转 NSNumber */
#define kNUMBER_DOUBLE(doubleValue)     [NSNumber numberWithDouble:doubleValue]
/** bool 转 NSNumber */
#define kNUMBER_BOOL(boolValue)         [NSNumber numberWithBool:boolValue]


#pragma mark -
#pragma mark NSString
#define kStringFormat(s)        [NSString stringWithFormat:@"%@",s]
#define kStringFromI(s)         [NSString stringWithFormat:@"%d",s]
#define kStringFromF(s)         [NSString stringWithFormat:@"%f",s]
#define kStringFromD(s)         [NSString stringWithFormat:@"%lf",s]
#define kStringVar(var)         [NSString stringWithFormat:@"%s",#var]

#pragma mark --
#pragma mark -- URL
#define kURLString(s)           [NSURL URLWithString:s]


#pragma mark --
#pragma mark -- 加载图片
#define kIMAGE_PNG_FILE(NAME)       [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(NAME) ofType:@"png"]]
#define kIMAGE_JPG_FILE(NAME)       [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(NAME) ofType:@"jpg"]]
#define kIMAGE_FILE(NAME, EXT)      [UIImage imageWithContentsOfFile:[[NSBundle mainBundle] pathForResource:(NAME) ofType:(EXT)]]
#define kIMAGE_NANED(NAME)          [UIImage imageNamed:NAME］

#pragma mark --
#pragma mark -- 颜色
#define kRGBA(r,g, b, a)  [UIColor colorWithRed:r/255.0f green:g/255.0f blue:b/255.0f alpha:a]
#define kRGB(r, g, b)     RGBA(r, g, b, 1.0f)
//随机色
#define GRandomColor      [UIColor colorWithRed:arc4random_uniform(256)/255.0 green:arc4random_uniform(256)/255.0 blue:arc4random_uniform(256)/255.0 alpha:1.0]

#define HEXColorA(rgbValue, a)   [UIColor colorWithRed:((float)(((rgbValue) & 0xFF0000) >> 16))/255.0 green:((float)(((rgbValue) & 0xFF00)>>8))/255.0 blue: ((float)((rgbValue) & 0xFF))/255.0 alpha:(a)]
#define HEXColorA(hex)          hexColorA(hex,1.0f)


#pragma mark --
#pragma mark -- 字体
#define kFontSize(size)     [UIFont systemFontOfSize:size]
#define kFontBSize(size)    [UIFont boldSystemFontOfSize:size]
#define kFontMSize(size)    [UIFont systemFontOfSize:size weight:(UIFontWeightMedium)]


/**
 * Creates \c __weak shadow variables for each of the variables provided as
 * arguments, which can later be made strong again with #strongify.
 *
 * This is typically used to weakly reference variables in a block, but then
 * ensure that the variables stay alive during the actual execution of the block
 * (if they were live upon entry).
 *
 * See #strongify for an example of usage.
 */
#define weakify(...) \
    rac_keywordify \
    metamacro_foreach_cxt(rac_weakify_,, __weak, __VA_ARGS__)

/**
 * Strongly references each of the variables provided as arguments, which must
 * have previously been passed to #weakify.
 *
 * The strong references created will shadow the original variable names, such
 * that the original names can be used without issue (and a significantly
 * reduced risk of retain cycles) in the current scope.
 *
 * @code

    id foo = [[NSObject alloc] init];
    id bar = [[NSObject alloc] init];

    @weakify(foo, bar);

    // this block will not keep 'foo' or 'bar' alive
    BOOL (^matchesFooOrBar)(id) = ^ BOOL (id obj){
        // but now, upon entry, 'foo' and 'bar' will stay alive until the block has
        // finished executing
        @strongify(foo, bar);

        return [foo isEqual:obj] || [bar isEqual:obj];
    };

 * @endcode
 */
#define strongify(...) \
    rac_keywordify \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wshadow\"") \
    metamacro_foreach(rac_strongify_,, __VA_ARGS__) \
    _Pragma("clang diagnostic pop")

#if DEBUG
#define rac_keywordify autoreleasepool {}
#else
#define rac_keywordify try {} @catch (...) {}
#endif



#endif /* YPMacros_h */
