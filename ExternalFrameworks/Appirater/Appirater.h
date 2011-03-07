/*
 This file is part of Appirater.
 
 Copyright (c) 2010, Arash Payan
 All rights reserved.
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 */
/*
 * Appirater.h
 * appirater
 *
 * Created by Arash Payan on 9/5/09.
 * http://arashpayan.com
 * Copyright 2010 Arash Payan. All rights reserved.
 */
// http://github.com/arashpayan/appirater

#import <Foundation/Foundation.h>

extern NSString *const kAppiraterFirstUseDate;
extern NSString *const kAppiraterUseCount;
extern NSString *const kAppiraterSignificantEventCount;
extern NSString *const kAppiraterCurrentVersion;
extern NSString *const kAppiraterRatedCurrentVersion;
extern NSString *const kAppiraterDeclinedToRate;

// All values can be overriden in your pch file

/*
 Place your Apple generated software id here.
 */
#ifndef APPIRATER_APP_ID
#define APPIRATER_APP_ID				346479957
#endif

/*
 Your app's name.
 */
#ifndef APPIRATER_APP_NAME
#define APPIRATER_APP_NAME				[[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString*)kCFBundleNameKey]
#endif

/*
 This is the message your users will see once they've passed the day+launches
 threshold.
 */
#ifndef APPIRATER_MESSAGE
#define APPIRATER_MESSAGE				[NSString stringWithFormat:NSLocalizedString(@"If you enjoy using %@, would you mind taking a moment to rate it? It won't take more than a minute. Thanks for your support!", @"Appirater"), APPIRATER_APP_NAME]
#endif

/*
 This is the title of the message alert that users will see.
 */
#ifndef APPIRATER_MESSAGE_TITLE
#define APPIRATER_MESSAGE_TITLE			[NSString stringWithFormat:NSLocalizedString(@"Rate %@", @"Appirater"), APPIRATER_APP_NAME]
#endif

/*
 The text of the button that rejects reviewing the app.
 */
#ifndef APPIRATER_CANCEL_BUTTON
#define APPIRATER_CANCEL_BUTTON			NSLocalizedString(@"No, Thanks", @"Appirater")
#endif

/*
 Text of button that will send user to app review page.
 */
#ifndef APPIRATER_RATE_BUTTON
#define APPIRATER_RATE_BUTTON			[NSString stringWithFormat:NSLocalizedString(@"Rate %@", @"Appirater"), APPIRATER_APP_NAME]
#endif

/*
 Text for button to remind the user to review later.
 */
#ifndef APPIRATER_RATE_LATER
#define APPIRATER_RATE_LATER			NSLocalizedString(@"Remind me later", @"Appirater")
#endif

/*
 Users will need to have the same version of your app installed for this many
 days before they will be prompted to rate it.
 */
#ifndef APPIRATER_DAYS_UNTIL_PROMPT
#define APPIRATER_DAYS_UNTIL_PROMPT		5		// double
#endif

/*
 An example of a 'use' would be if the user launched the app. Bringing the app
 into the foreground (on devices that support it) would also be considered
 a 'use'. You tell Appirater about these events using the two methods:
 [Appirater appLaunched:]
 [Appirater appEnteredForeground:]
 
 Users need to 'use' the same version of the app this many times before
 before they will be prompted to rate it.
 */
#ifndef APPIRATER_USES_UNTIL_PROMPT
#define APPIRATER_USES_UNTIL_PROMPT		5		// integer
#endif

/*
 A significant event can be anything you want to be in your app. In a
 telephone app, a significant event might be placing or receiving a call.
 In a game, it might be beating a level or a boss. This is just another
 layer of filtering that can be used to make sure that only the most
 loyal of your users are being prompted to rate you on the app store.
 If you leave this at a value of -1, then this won't be a criteria
 used for rating. To tell Appirater that the user has performed
 a significant event, call the method:
 [Appirater userDidSignificantEvent:];
 */
#ifndef APPIRATER_SIG_EVENTS_UNTIL_PROMPT
#define APPIRATER_SIG_EVENTS_UNTIL_PROMPT	3	// integer
#endif

/*
 Once the rating alert is presented to the user, they might select
 'Remind me later'. This value specifies how long (in days) Appirater
 will wait before reminding them.
 */
#ifndef APPIRATER_TIME_BEFORE_REMINDING
#define APPIRATER_TIME_BEFORE_REMINDING	7	// double
#endif

/*
 'YES' will show the Appirater alert everytime. Useful for testing how your message
 looks and making sure the link to your app's review page works.
 */
#ifndef APPIRATER_DEBUG
#define APPIRATER_DEBUG				YES
#endif

@interface Appirater : NSObject <UIAlertViewDelegate> {

}

/*
 DEPRECATED: While still functional, it's better to use
 appLaunched:(BOOL)canPromptForRating instead.
 
 Calls [Appirater appLaunched:YES]. See appLaunched: for details of functionality.
 */
+ (void)appLaunched;

/*
 Tells Appirater that the app has launched, and on devices that do NOT
 support multitasking, the 'uses' count will be incremented. You should
 call this method at the end of your application delegate's
 application:didFinishLaunchingWithOptions: method.
 
 If the app has been used enough to be rated (and enough significant events),
 you can suppress the rating alert
 by passing NO for canPromptForRating. The rating alert will simply be postponed
 until it is called again with YES for canPromptForRating. The rating alert
 can also be triggered by appEnteredForeground: and userDidSignificantEvent:
 (as long as you pass YES for canPromptForRating in those methods).
 */
+ (void)appLaunched:(BOOL)canPromptForRating;

/*
 Tells Appirater that the app was brought to the foreground on multitasking
 devices. You should call this method from the application delegate's
 applicationWillEnterForeground: method.
 
 If the app has been used enough to be rated (and enough significant events),
 you can suppress the rating alert
 by passing NO for canPromptForRating. The rating alert will simply be postponed
 until it is called again with YES for canPromptForRating. The rating alert
 can also be triggered by appLaunched: and userDidSignificantEvent:
 (as long as you pass YES for canPromptForRating in those methods).
 */
+ (void)appEnteredForeground:(BOOL)canPromptForRating;

/*
 Tells Appirater that the user performed a significant event. A significant
 event is whatever you want it to be. If you're app is used to make VoIP
 calls, then you might want to call this method whenever the user places
 a call. If it's a game, you might want to call this whenever the user
 beats a level boss.
 
 If the user has performed enough significant events and used the app enough,
 you can suppress the rating alert by passing NO for canPromptForRating. The
 rating alert will simply be postponed until it is called again with YES for
 canPromptForRating. The rating alert can also be triggered by appLaunched:
 and appEnteredForeground: (as long as you pass YES for canPromptForRating
 in those methods).
 */
+ (void)userDidSignificantEvent:(BOOL)canPromptForRating;

@end
