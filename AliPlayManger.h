//
//  AliPlayManger.h
//  AliyunVideoClient_Entrance
//
//  Created by 刘家伟 on 2020/7/26.
//  Copyright © 2020 Aliyun. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AliyunPlayer/AliyunPlayer.h>
#import "AlivcLongVideoPlayView.h"
#import "AliyunUtil.h"
#import "AliyunPlayerFinishView.h"
#import "AliyunReachability.h"
#import "AlivcLongVideoDownLoadProgressManager.h"
#import "AlivcLongVideoCommonFunc.h"
#import "AlivcLongVideoDefinitionSelectView.h"
#import <MBProgressHUD+AlivcHelper.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, PlayStatus) {
    /// 正在播放
    PlayStatusPlaying,
    /// 暂停播放
    PlayStatusPause,
    /// 未播放
    PlayStatusNoPlay,
    /// 播放出错
    PlayStatusPlayError,
};

typedef NS_ENUM(NSUInteger, DownloadStatus) {
    /// 停止
    DownloadStatusStop,
    /// 等待
    DownloadStatusWaiting,
    /// 下载中
    DownloadStatusLoading,
    /// 下载完成
    DownloadStatusFinish,
    /// 准备完成
    DownloadStatusPrepared,
    /// 下载失败
    DownloadStatusFailed,
};

/// 屏幕旋转通知
static NSString *InterfaceOrientationNotificationName = @"InterfaceOrientationChange";

/// 播放器管理
@interface AliPlayManger : NSObject<AliyunVodPlayerViewDelegate, AlivcLongVideoDownLoadProgressManagerDelegate, AlivcLongVideoDefinitionSelectViewDelegate>

/// 播放器对象
@property (nonatomic, strong) AlivcLongVideoPlayView *playerView;
/// 完成播放后视图
@property (nonatomic, strong) AliyunPlayerFinishView *finishView;
/// video ID数组
@property (nonatomic, copy) NSArray <NSString *>*vidsArray;
/// 网络监听
@property (nonatomic, strong) AliyunReachability *reachability;
/// 下载器进度管理
@property (nonatomic, strong) AlivcLongVideoDownLoadProgressManager *downLoadProgressManager;
/// 下载器管理
@property (nonatomic, strong) AlivcLongVideoDownLoadManager *downLoadManager;
/// 选择清晰度视图
@property (nonatomic, strong) AlivcLongVideoDefinitionSelectView *definitionSelectView;
/// 正在下载的资源
@property (nonatomic, strong) AlivcLongVideoDownloadSource *currentDownloadSource;


#pragma mark --------------------------- 初始化播放器和基础功能 -----------------------------
/// 初始化播放器
/// @param frame 播放器视图坐标
- (instancetype)initWithFrame:(CGRect)frame;

/// 设置播放列表
/// @param VidArray 播放列表数组，里面转载的是 videoid
- (void)setPlayListsWithVideoIdsArray:(NSArray <NSString *>*)VidArray;

/// STS鉴权播放播放
/// @param vid 视频ID
/// @param auth 鉴权
- (void)playerWithVid:(NSString *)vid playAuth:(NSString *)auth;

/// playAuth鉴权播放播放
/// @param vid 视频ID
- (void)playerWithVid:(NSString *)vid;

/// 开始Vid地址播放
- (void)startVidPlay;

/// 自动播放下一个
- (void)moveToNext;
/// 播放下一个
- (void)changePlayVidSource:(NSString *)vid;

/// 开始播放
- (void)start;

/// 停止播放
- (void)stop;

/**
 功能：重载播放
 */
- (void)reload;

/// 重新播放
- (void)rePlay;

/**
 功能：暂停播放视频
 */
- (void)pause;

/**
 功能：继续播放视频，此功能应用于pause之后，与pause功能匹配使用
 */
- (void)resume;
/**
 功能：seek到某个时间播放视频
 */
- (void)seekTo:(NSTimeInterval)seekTime;

/**
 功能：释放播放器
 */
- (void)releasePlayer;

/// 设置成静音
/// @param muted 静音标识
- (void)setMuted:(BOOL)muted;

/// 设置音量
/// @param volum 音量大小 0~1
- (void)setVolum:(CGFloat)volum;

/// 播放速度 0.5-2.0之间，1为正常播放
/// @param speedValue 0.5-2.0之间，1为正常播放
- (void)changeSpeed:(CGFloat)speedValue;

/// 播放本地视频文件
/// @param path 视频文件地址
- (void)playWithLocalSource:(NSString *)path;

/// 全屏播放
- (void)setScreenFull;

/// 设置亮度
/// @param brightness 亮度
- (void)setWindowBrightness:(CGFloat)brightness;

#pragma mark - ------------------- 下载接口 -------------------------------

/// 准备下载资源
/// @param vid 资源的videoID 不传值表示下载当前播放的视频
/// @param auth 资源的鉴权 不传值表示下载当前播放的视频
/// @param path 资源保存的地址 必传值
- (void)startDownLoad:(NSString *)vid playAuth:(NSString *)auth withPath:(NSString *)path;

/*
 功能：清除指定下载的视频资源
 参数：downloadSource 要删除的视频资源
 */
- (void)deleteFile:(NSString *)path;

/// 获取已经下载完成的视频文件地址列表
- (NSArray <NSString *>*)getDoneDownLoadSource;

/// 获取正在下载的资源地址
- (NSString *)getDownloadingSource;

/*
 功能：清除所有准备的的视频资源
 */
- (void)clearAllSources;

/// 停止下载
- (void)stopDownload;

/// 继续下载
- (void)continueDownload;

#pragma mark - -------------------------- 试看接口 -------------------------------

- (void)setTrailerTime:(CGFloat)time;

#pragma mark ------------------------------ 文件加密 ----------------------------

/// 播放加密，在初始化的时候已经做了播放加密，除非需要更换加密文件，否则不需要调用此方法
- (void)encry:(NSString *)encryptPath;

#pragma mark ---------------------------- 获取playauth -------------------------
- (void)getVideoPlayAuthInfoWithVideoId:(NSString *)vid block:(void(^)(NSString *playAuth))block;


#pragma mark ---------------------------- 新接口 0.1.3.1版本 -----------------------------------
/// 新的初始化方法
/// @param frame 视频播放器的坐标
/// @param baseUrl 视频播放器的域名
/// @param path 视频播放器的扩展地址
- (instancetype)initWithFrame:(CGRect)frame withBaseUrl:(NSString *)baseUrl withPath:(NSString *)path;
/// 获取播放视图
- (UIView *)getPlayView;

#pragma mark -------------------------- 新接口 0.1.3.2版本 2020-08-05 ----------------------------
/// 播放状态更新
@property (nonatomic, copy) void(^playStatusBlock)(PlayStatus status, AlivcLongVideoPlayView *playV);
/// 当前播放状态
@property (nonatomic, assign) PlayStatus currentPlayStatus;

/// 下载状态更新
@property (nonatomic, copy) void(^downLoadStatusBlock)(DownloadStatus status, AlivcLongVideoDownLoadManager *downloadMan);
/// 当前下载状态
@property (nonatomic, assign) DownloadStatus currentDownloadStatus;
/// 下载进度回调
@property (nonatomic, copy) void(^downloadProgressBlock)(int progress, AlivcLongVideoDownLoadProgressManager *progressMan);

/// 更新playAuth
/// @param vid 视频ID
/// @param block 回调
- (void)UpdateVideoPlayAuthInfoWithVideoId:(NSString *)vid block:(void(^)(NSString *playAuth))block;
/// 更新playAuth后直接播放
/// @param vid 视频ID
/// @param block 回调
- (void)UpdateVideoPlayAuthAndPlayingWithVideoId:(NSString *)vid block:(void(^)(NSString *playAuth))block;
/// 是否是全屏的状态值回调
@property (nonatomic, copy) void(^interfaceOrientationChangeBlock)(BOOL isFullScreen);

#pragma mark --------------------------------- 2020-08-10 ---------------------------------
/// 视频播放进度回调 progress取值范围是0-100
@property (nonatomic, copy) void(^playProgressBlock)(NSInteger progress);

#pragma mark ---------------------------------- 2020-08-13 --------------------------------
/// 下载进度回调和下载状态
/* status的类型值
    LongVideoDownloadTypeStoped,    //停止
    LongVideoDownloadTypeWaiting,    //等待
    LongVideoDownloadTypeLoading, //下载中
    LongVideoDownloadTypefinish,  //已完成
    LongVideoDownloadTypePrepared,//准备完成
    LongVideoDownloadTypeFailed // 下载失败
*/
@property (nonatomic, copy) void(^downloadStatusAndProgress)(LongVideoDownloadType status, int progress);

/*
 功能：清除指定下载的视频资源
 参数：downloadSource 要删除的视频资源
 */
- (BOOL)deleteFileWithPath:(NSString *)path;

#pragma mark ------------------------------- 2020-08-14 ----------------------------------
/// 视频播放进度回调 progress取值范围是0-100, time 是当前播放时间
@property (nonatomic, copy) void(^playProgressAndTimerBlock)(NSInteger progress, NSTimeInterval time);

@end

NS_ASSUME_NONNULL_END
