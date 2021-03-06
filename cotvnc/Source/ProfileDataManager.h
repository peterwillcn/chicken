//
//  ProfileDataManager.h
//  Chicken of the VNC
//
//  Created by Jared McIntyre on 8/12/04.
//  Copyright 2004 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/** This message indicates that the profile list has changed */
extern NSNotificationName const ProfileListChangeMessgageNotification;
#define ProfileListChangeMsg ProfileListChangeMessgageNotification

@class Profile;

@interface ProfileDataManager : NSObject {

@private
	NSMutableDictionary<NSString*,Profile*> *mProfiles;
    NSMutableDictionary *mProfileDicts;
}

/**
 *  Accessor method to fetch the singleton instance for this class. Use this method
 *  instead of creating an instance of your own.
 *  @return Shared singleton instance of the ProfileDataManager class. */
@property (class, readonly) ProfileDataManager *sharedInstance NS_SWIFT_NAME(shared);

- (Profile *)defaultProfile;
- (NSString *)defaultProfileName;
- (Profile *)profileForKey:(id) key;
- (BOOL)profileWithNameExists:(NSString *)name;
- (void)setProfile:(Profile*) profile forKey:(id) key;
- (void)removeProfileForKey:(id) key;
@property (readonly) NSInteger count;
- (void)saveProfile:(Profile *)profile;
- (NSArray*)sortedKeyArray;

@end
