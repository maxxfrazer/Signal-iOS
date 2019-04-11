//
//  Copyright (c) 2019 Open Whisper Systems. All rights reserved.
//

#import "TSThread.h"

NS_ASSUME_NONNULL_BEGIN

extern NSString *const TSContactThreadPrefix;

@interface TSContactThread : TSThread

- (instancetype)initWithUniqueId:(nullable NSString *)uniqueId
                    archivalDate:(nullable NSDate *)archivalDate
       archivedAsOfMessageSortId:(nullable NSNumber *)archivedAsOfMessageSortId
           conversationColorName:(NSString *)conversationColorName
                    creationDate:(NSDate *)creationDate
isArchivedByLegacyTimestampForSorting:(BOOL)isArchivedByLegacyTimestampForSorting
                 lastMessageDate:(nullable NSDate *)lastMessageDate
                    messageDraft:(nullable NSString *)messageDraft
                  mutedUntilDate:(nullable NSDate *)mutedUntilDate
           shouldThreadBeVisible:(BOOL)shouldThreadBeVisible
              hasDismissedOffers:(BOOL)hasDismissedOffers
NS_SWIFT_NAME(init(uniqueId:archivalDate:archivedAsOfMessageSortId:conversationColorName:creationDate:isArchivedByLegacyTimestampForSorting:lastMessageDate:messageDraft:mutedUntilDate:shouldThreadBeVisible:hasDismissedOffers:));

// TODO: We might want to make this initializer private once we
//       convert getOrCreateThreadWithContactId to take "any" transaction.
- (instancetype)initWithContactId:(NSString *)contactId;

@property (nonatomic) BOOL hasDismissedOffers;

+ (instancetype)getOrCreateThreadWithContactId:(NSString *)contactId NS_SWIFT_NAME(getOrCreateThread(contactId:));

+ (instancetype)getOrCreateThreadWithContactId:(NSString *)contactId
                                   transaction:(YapDatabaseReadWriteTransaction *)transaction;

// Unlike getOrCreateThreadWithContactId, this will _NOT_ create a thread if one does not already exist.
+ (nullable instancetype)getThreadWithContactId:(NSString *)contactId transaction:(YapDatabaseReadTransaction *)transaction;

- (NSString *)contactIdentifier;

+ (NSString *)contactIdFromThreadId:(NSString *)threadId;

// This is only exposed for tests.
#ifdef DEBUG
+ (NSString *)threadIdFromContactId:(NSString *)contactId;
#endif

// This method can be used to get the conversation color for a given
// recipient without using a read/write transaction to create a
// contact thread.
+ (NSString *)conversationColorNameForRecipientId:(NSString *)recipientId
                                      transaction:(YapDatabaseReadTransaction *)transaction;

@end

NS_ASSUME_NONNULL_END
