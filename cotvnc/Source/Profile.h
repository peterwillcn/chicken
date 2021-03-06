/* Profile.h created by helmut on Fri 25-Jun-1999 */

/* Copyright (C) 1998-2000  Helmut Maierhofer <helmut.maierhofer@chello.at>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#import <AppKit/AppKit.h>
#import "EventFilter.h"
#import "rfbproto.h"
#import "ProfileManager.h"

//! Modifier Key Mapping
//! These values are the values stored in preferences, and must remain in sync
//! with the order in the ProfileManager pulldowns
typedef NS_ENUM(int, ModifierKeyIdentifier) {
	kRemoteAltModifier		= 0,
	kRemoteMetaModifier		= 1,
	kRemoteControlModifier	= 2,
	kRemoteShiftModifier	= 3,
	kRemoteWindowsModifier	= 4,
    kRemoteNoModifier       = 5
};

// Dictionary Keys
extern NSString *const kProfile_PixelFormat_Key;
extern NSString *const kProfile_EnableCopyrect_Key;
extern NSString *const kProfile_EnableJpegEncoding_Key;
extern NSString *const kProfile_JpegQualityLevel_Key;
extern NSString *const kProfile_Encodings_Key;
extern NSString *const kProfile_EncodingValue_Key;
extern NSString *const kProfile_EncodingEnabled_Key;
extern NSString *const kProfile_LocalAltModifier_Key;
extern NSString *const kProfile_LocalCommandModifier_Key;
extern NSString *const kProfile_LocalControlModifier_Key;
extern NSString *const kProfile_LocalShiftModifier_Key;
extern NSString *const kProfile_InterpretModifiersLocally_Key;
extern NSString *const kProfile_Button2EmulationScenario_Key;
extern NSString *const kProfile_Button3EmulationScenario_Key;
extern NSString *const kProfile_ClickWhileHoldingModifierForButton2_Key;
extern NSString *const kProfile_ClickWhileHoldingModifierForButton3_Key;
extern NSString *const kProfile_MultiTapModifierForButton2_Key;
extern NSString *const kProfile_MultiTapModifierForButton3_Key;
extern NSString *const kProfile_MultiTapDelayForButton2_Key;
extern NSString *const kProfile_MultiTapDelayForButton3_Key;
extern NSString *const kProfile_MultiTapCountForButton2_Key;
extern NSString *const kProfile_MultiTapCountForButton3_Key;
extern NSString *const kProfile_TapAndClickModifierForButton2_Key;
extern NSString *const kProfile_TapAndClickModifierForButton3_Key;
extern NSString *const kProfile_TapAndClickButtonSpeedForButton2_Key;
extern NSString *const kProfile_TapAndClickButtonSpeedForButton3_Key;
extern NSString *const kProfile_TapAndClickTimeoutForButton2_Key;
extern NSString *const kProfile_TapAndClickTimeoutForButton3_Key;
extern NSString *const kProfile_IsDefault_Key;

extern NSNotificationName const ProfileTintChangedNotification;
extern NSNotificationName const ProfileEncodingsChangedNotification;

#define ProfileTintChangedMsg ProfileTintChangedNotification
#define ProfileEncodingsChangedMsg ProfileEncodingsChangedNotification

// Encodings
#define NUMENCODINGS					8
extern const unsigned int gEncodingValues[];

struct encoding {
    CARD32  encoding;
    BOOL    enabled;
};

@interface Profile : NSObject
{
    NSString *name;
    BOOL isDefault;
    NSInteger pixelFormatIndex;

    ModifierKeyIdentifier commandKeyPreference;
    ModifierKeyIdentifier altKeyPreference;
    ModifierKeyIdentifier shiftKeyPreference;
    ModifierKeyIdentifier controlKeyPreference;

    // encodings
    CARD16 numberOfEnabledEncodings;
    CARD32 *enabledEncodings; // enabled encodings, including pseudo
    BOOL enableCopyRect;
    int jpegLevel;
    struct encoding *encodings; // all non-pseudo encodings, even disabled
    NSInteger numEncodings;

    // emulation
	EventFilterEmulationScenario _buttonEmulationScenario[2];
	NSEventModifierFlags _clickWhileHoldingModifier[2];
	NSEventModifierFlags _multiTapModifier[2];
	NSTimeInterval _multiTapDelay[2]; // 0 means double click interval
	NSInteger _multiTapCount[2];
	NSEventModifierFlags _tapAndClickModifier[2];
	NSTimeInterval _tapAndClickButtonSpeed[2]; // 0 means double click interval
	NSTimeInterval _tapAndClickTimeout[2];

    NSColor *tintFront;
    NSColor *tintBack;
}

- (instancetype)init;
- (instancetype)initWithDictionary:(NSDictionary*)d name: (NSString *)name;
- (instancetype)initWithProfile: (Profile *)profile andName: (NSString *)aName;
- (void)makeEnabledEncodings;
- (NSDictionary *)dictionary;
@property (readonly, copy) NSString *profileName;
@property (readonly, getter=isDefault) BOOL isDefault;

@property (readonly) CARD32 commandKeyCode;
@property (readonly) CARD32 altKeyCode;
@property (readonly) CARD32 shiftKeyCode;
@property (readonly) CARD32 controlKeyCode;
@property ModifierKeyIdentifier commandKeyPreference;
@property ModifierKeyIdentifier altKeyPreference;
@property ModifierKeyIdentifier shiftKeyPreference;
@property ModifierKeyIdentifier controlKeyPreference;
@property NSInteger pixelFormatIndex;
- (CARD16)numEnabledEncodingsIfViewOnly:(BOOL)viewOnly;
- (CARD32)encodingAtIndex:(unsigned)index;
@property (readonly) BOOL enableCopyRect;
@property (readonly) BOOL enableJpegEncoding;
@property (nonatomic) int jpegLevel;
@property (readonly) BOOL useServerNativeFormat;
- (void)getPixelFormat:(rfbPixelFormat*)format;
@property (readonly) EventFilterEmulationScenario button2EmulationScenario;
@property (readonly) EventFilterEmulationScenario button3EmulationScenario;
- (NSEventModifierFlags)clickWhileHoldingModifierForButton: (unsigned int)button;
- (NSEventModifierFlags)multiTapModifierForButton: (unsigned int)button;
- (NSTimeInterval)multiTapDelayForButton: (unsigned int)button;
- (NSInteger)multiTapCountForButton: (unsigned int)button;
- (NSEventModifierFlags)tapAndClickModifierForButton: (unsigned int)button;
- (NSTimeInterval)tapAndClickButtonSpeedForButton: (unsigned int)button;
- (NSTimeInterval)tapAndClickTimeoutForButton: (unsigned int)button;
@property (readonly) BOOL interpretModifiersLocally;
@property (readonly) NSInteger numEncodings;
- (NSString *)encodingNameAtIndex: (NSInteger)index;
- (BOOL)encodingEnabledAtIndex: (NSInteger)index;
- (NSColor *)tintWhenFront:(BOOL)front;

- (void)setEmulationScenario:(EventFilterEmulationScenario)scenario
                   forButton:(unsigned)button;
- (void)setClickWhileHoldingModifier:(NSEventModifierFlags)modifier
                           forButton:(unsigned)button;
- (void)setMultiTapModifier:(NSEventModifierFlags)modifier forButton:(unsigned)button;
- (void)setMultiTapCount: (NSInteger)count forButton:(unsigned)button;
- (void)setMultiTapDelay:(NSTimeInterval)delay forButton:(unsigned) button;
- (void)setTapAndClickModifier:(NSEventModifierFlags)modifer forButton:(unsigned)button;
- (void)setTapAndClickButtonSpeed:(NSTimeInterval)speed
                        forButton:(unsigned)button;
- (void)setTapAndClickTimeout:(NSTimeInterval)timeout
                    forButton:(unsigned)button;
- (void)setEncodingEnabled:(BOOL)enabled atIndex:(NSInteger)index;
- (void)moveEncodingFrom:(NSInteger)src to:(NSInteger)dst;
- (void)setCopyRectEnabled:(BOOL)enabled;
- (void)setJpegEncodingEnabled:(BOOL)enabled;
- (void)setJpegLevel:(int)level;
- (void)setTint:(NSColor *)aTint whenFront:(BOOL)front;

@end
