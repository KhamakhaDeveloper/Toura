#import <Foundation/Foundation.h>
#import <KudanAR/ARPlayableTexture.h>
#import <KudanAR/ARRenderer.h>
#import <AVFoundation/AVFoundation.h>

/**
 An ARVideoTexture represents a texture capable of rendering videos.
 **/
@interface ARVideoTexture : ARPlayableTexture <ARRendererDelegate, AVAudioPlayerDelegate, NSCopying>

/**
 Whether or not this video texture has been added to the video manager and is ready to be played.
 If a video is already active, it cannot be activated, meaning it a video texture cannot be added to the video manager more than once.
 If a video is not active, it cannot be spilled, meaning it effectively cannot be removed from the video manager, even if there is no room when a new video texture is added.
 **/
@property (nonatomic) BOOL isActive;

/**
 Current video time in seconds.
 **/
@property (nonatomic) double currentVideoTime;

/**
 Time of last frame rendered in seconds.
 **/
@property (nonatomic) double lastRenderTime;

/**
 Initialises video texture with audio file.
 
 @param videoFile Filepath to the video file. This can be either a full filepath or a path relative to the main bundle.
 Supported video formats are the same as those supported by Apple.
 @param audioFile Filepath to the audio file. This can be either a full filepath or a path relative to the main bundle.
 Supported audio formats are the same as those supported by AVAudioPlayer.
 
 @return A new ARVideoTexture with a video track from the given video file and an audio track from the given audio file.
 **/
- (instancetype)initWithVideoFile:(NSString *)videoFile audioFile:(NSString *)audioFile;

/**
 Removes video texture from cache.
 **/
- (void)spill;

/**
 Adds this video texture to the video manager, resets it and activates it. 
 If there's no room this texture will overwrite the oldest video texture in the video manager's array of textures.
 The Video manager can hold 3 video textures at once.
 **/
- (void)activate;

@end
