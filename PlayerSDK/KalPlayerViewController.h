//
//  KalPlayerViewController.h
//  HelloWorld
//
//  Created by Eliza Sapir on 9/11/13.
//
//

/* This class is responsible for player sdk
 in this class we have a player which contains a webview as subview, the webview reflects html5 NativeComponent */

// Copyright (c) 2013 Kaltura, Inc. All rights reserved.
// License: http://corp.kaltura.com/terms-of-use
//

#import <MediaPlayer/MediaPlayer.h>
#import "PlayerControlsWebView.h"

typedef enum{
    // Player Content Source Url
    src = 0,
    // Player Current time (Progress Bar)
    currentTime,
    // Player Visibility
    visible,
  #if !(TARGET_IPHONE_SIMULATOR)
        // DRM WideVine Key
        wvServerKey,
    #endif
} Attribute;

// JSCallbackReady Handler Block
typedef void (^JSCallbackReadyHandler)();

@class KalPlayerViewController;
@class NativeComponentPlugin;
@class KPEventListener;

@protocol KalPlayerViewControllerDelegate;
@protocol KalturaPlayer <NSObject>

@required

@property double currentPlaybackTime;
@property(readonly) UIView * view;
@property(readonly) int playbackState;
@property(readonly) int loadState;
@property(readonly) BOOL isPreparedToPlay;

@property (nonatomic, retain) id<KalPlayerViewControllerDelegate> delegate;
+ (id)alloc;

-(int)getControlStyle;
-(void)setControlStyle:(int)cs;

-(NSURL *)contentURL;
-(void)setContentURL:(NSURL *)cs;

- (void)pause;
- (void)play;
- (void)stop;
//- (id)view;
- (double)currentPlaybackTime;
//- (int)controlStyle;
- (int)playbackState;
//- (int)loadState;
//- (void)prepareToPlay;
- (BOOL)isPreparedToPlay;
- (double)playableDuration;
- (double)duration;

@optional
- (id)view;
- (int)controlStyle;
- (void)prepareToPlay;
- (int)loadState;

- (void)didLoad;
- (CGFloat) getCurrentTime;
- (instancetype) initWithFrame:(CGRect)frame forView:(UIView *)parentView;
- (void) copyParamsFromPlayer:(id<KalturaPlayer>) player;
//- (void)setWebViewURL: (NSString *)iframeUrl;

@end


@protocol KalPlayerViewControllerDelegate <NSObject>

@required

@property (nonatomic, retain) id<KalPlayerViewControllerDelegate> kalPlayerViewControllerDelegate;
-(NSURL *)getInitialKIframeUrl;

@optional
- (void) kPlayerDidPlay;
- (void) kPlayerDidPause;
- (void) kPlayerDidStop;

@end

@protocol KDPApi <NSObject>

@optional
// Kaltura Player External API
- (void)registerJSCallbackReady: (JSCallbackReadyHandler)handler;
- (void)addKPlayerEventListener: (NSString *)name forListener: (KPEventListener *)listener;
- (void)removeKPlayerEventListenerWithEventName: (NSString *)name forListenerName: (NSString *)listenerName;
- (void)asyncEvaluate: (NSString *)expression forListener: (KPEventListener *)listener;
- (void)sendNotification: (NSString*)notificationName andNotificationBody: (NSString *)notificationBody;
- (void)setKDPAttribute: (NSString*)pluginName propertyName: (NSString*)propertyName value: (NSString*)value;
- (void)triggerEventsJavaScript: (NSString *)eventName WithValue: (NSString *) eventValue;

@end

@interface KalPlayerViewController : UIViewController <PlayerControlsWebViewDelegate, KDPApi> {
    id<KalturaPlayer> player;
    NativeComponentPlugin *nativComponentDelegate;
    id<KalPlayerViewControllerDelegate> kalPlayerViewControllerDelegate;
}

@property (nonatomic, strong) IBOutlet PlayerControlsWebView* webView;
@property (nonatomic, retain) NativeComponentPlugin *nativComponentDelegate;
@property (nonatomic, strong) id<KalturaPlayer> player;
@property (readwrite, nonatomic, copy) JSCallbackReadyHandler jsCallbackReadyHandler;

- (instancetype) initWithFrame:(CGRect)frame forView:(UIView *)parentView;
//- (void)setWebViewURL: (NSString *)iframeUrl;
- (void)stopAndRemovePlayer;
- (void)checkOrientationStatus;
- (void)resizePlayerView: (CGFloat )top right: (CGFloat )right width: (CGFloat )width height: (CGFloat )height;
- (void)openFullscreen;
- (void)closeFullscreen;
- (void)checkDeviceStatus;
- (void)setNativeFullscreen;
- (void)setWebViewURL: (NSString *)iframeUrl;
+ (id)sharedChromecastDeviceController;

// Kaltura Player External API
- (void)registerJSCallbackReady: (JSCallbackReadyHandler)handler;
- (void)addKPlayerEventListener: (NSString *)name forListener: (KPEventListener *)listener;
- (void)removeKPlayerEventListenerWithEventName: (NSString *)name forListenerName: (NSString *)listenerName;
- (void)asyncEvaluate: (NSString *)expression forListener: (KPEventListener *)listener;
- (void)sendNotification: (NSString*)notificationName andNotificationBody: (NSString *)notificationBody;
- (void)setKDPAttribute: (NSString*)pluginName propertyName: (NSString*)propertyName value: (NSString*)value;
- (void)triggerEventsJavaScript: (NSString *)eventName WithValue: (NSString *) eventValue;

@property (nonatomic, retain) NSMutableDictionary *players;

@end

@interface NSString (EnumParser)

- (Attribute)attributeNameEnumFromString;

@end
