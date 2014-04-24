//
//  NSObject+EFMapping.h
//  EFMapping
//
//  Created by Johan Kool on 20/3/2014.
//  Copyright (c) 2014 Johan Kool. All rights reserved.
//

#import <Foundation/Foundation.h>







@protocol EFTransforms <NSObject>


@end




/**
 *  Classes return an array of EFMapping instances to define how data from an external source, such as JSON, needs to be applied to its instances.
 */
@interface EFMapping : NSObject

#pragma mark - Number (incl. BOOL, integer, floats etc.)
+ (instancetype)mappingForNumberWithKey:(NSString *)key;
+ (instancetype)mappingForNumberWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey;
+ (instancetype)mappingForNumberWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey formatter:(NSFormatter *)formatter;
+ (instancetype)mappingForNumberWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformer:(NSValueTransformer *)transformer;
+ (instancetype)mappingForNumberWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformationBlock:(EFMappingTransformationBlock)transformationBlock;

#pragma mark - NSString
+ (instancetype)mappingForStringWithKey:(NSString *)key;
+ (instancetype)mappingForStringWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey;
+ (instancetype)mappingForStringWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey formatter:(NSFormatter *)formatter;
+ (instancetype)mappingForStringWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformer:(NSValueTransformer *)transformer;
+ (instancetype)mappingForStringWithExternalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformationBlock:(EFMappingTransformationBlock)transformationBlock;

#pragma mark - Classes
+ (instancetype)mappingForClass:(Class)internalClass from:(NSString *)externalKey to:(NSString *)internalKey transforms:(id <EFTransforms>)transforms requires:(id <EFRequires>)requirements;

+ (instancetype)mappingForClass:(Class)internalClass key:(NSString *)key;
+ (instancetype)mappingForClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey;
+ (instancetype)mappingForClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey requires:(id <EFRequires>)requirements;
+ (instancetype)mappingForClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey formatter:(NSFormatter *)formatter;
+ (instancetype)mappingForClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformer:(NSValueTransformer *)transformer;
+ (instancetype)mappingForClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformationBlock:(EFMappingTransformationBlock)transformationBlock;

#pragma mark - NSArray of classes
+ (instancetype)mappingForArrayOfClass:(Class)internalClass key:(NSString *)key;
+ (instancetype)mappingForArrayOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey;
+ (instancetype)mappingForArrayOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey formatter:(NSFormatter *)formatter;
+ (instancetype)mappingForArrayOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformer:(NSValueTransformer *)transformer;
+ (instancetype)mappingForArrayOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformationBlock:(EFMappingTransformationBlock)transformationBlock;

#pragma mark - NSDictionary of classes
+ (instancetype)mappingForDictionaryOfClass:(Class)internalClass key:(NSString *)key;
+ (instancetype)mappingForDictionaryOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey;
+ (instancetype)mappingForDictionaryOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey formatter:(NSFormatter *)formatter;
+ (instancetype)mappingForDictionaryOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformer:(NSValueTransformer *)transformer;
+ (instancetype)mappingForDictionaryOfClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformationBlock:(EFMappingTransformationBlock)transformationBlock;

#pragma mark - Generic collection of classes
+ (instancetype)mappingForCollection:(Class)collectionClass ofClass:(Class)internalClass key:(NSString *)key;
+ (instancetype)mappingForCollection:(Class)collectionClass ofClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey;
+ (instancetype)mappingForCollection:(Class)collectionClass ofClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey formatter:(NSFormatter *)formatter;
+ (instancetype)mappingForCollection:(Class)collectionClass ofClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformer:(NSValueTransformer *)transformer;
+ (instancetype)mappingForCollection:(Class)collectionClass ofClass:(Class)internalClass externalKey:(NSString *)externalKey internalKey:(NSString *)internalKey transformationBlock:(EFMappingTransformationBlock)transformationBlock;

@end


@interface EFMapper : NSObject

- (void)registerMappings:(NSArray *)mappings forClass:(Class)aClass;
- (void)registerInstantiationBlock:(EFMappingInstantiationBlock)instantiationBlock forClass:(Class)aClass;
- (BOOL)validateValues:(NSDictionary *)values forClass:(Class)aClass error:(NSError **)error;
- (BOOL)setValues:(NSDictionary *)values onObject:(id)object error:(NSError **)error;
- (id)objectOfClass:(Class)aClass withValues:(NSDictionary *)values error:(NSError **)error;

- (void)encodeObject:(id)object withCoder:(NSCoder *)aCoder;
- (void)decodeObject:(id)object withCoder:(NSCoder *)aDecoder;

- (id)copyObject:(id)object deepCopy:(BOOL)deepCopy;

- (void)registerDictionaryRepresentationKeys:(NSArray *)keys forClass:(Class)aClass;
- (id)dictionaryRepresentationOfObject:(id)object forKeys:(NSArray *)keys;
- (id)dictionaryRepresentationOfObject:(id)object;

@end

/**
 *  Category on NSObject that maps data such as those coming from JSON onto an instance using mappings. The mappings are also used to simplify implementing the NSCoding protocol for a class, and to create a dictionary representation of an instance.
 */
@interface NSObject (EFMapping)

#pragma mark - Mappings
/**
 *  Mappings to be used for setting values on instances of this class
 *
 *  Default implementation returns nil.
 *
 *  @return Array of EFMapping instances
 */
+ (NSArray *)mappings;

#pragma mark - Validating and applying values
/**
 *  Validate values to be applied to instance
 *
 *  Verifies wether the values in a dictionary can be successfully applied on the instance of a class using its mappings. This basically means that values get checked on wether they are of the right type. Instances get a chance to validate a value using the standard KVO validation. To use this implement -[validate<Key>:error:] method in your class.
 *
 *  @param values The values to be validated
 *  @param error  Error when invalid values are encountered
 *
 *  @return YES if all values are valid, NO otherwise
 */
- (BOOL)validateValues:(NSDictionary *)values error:(NSError **)error;

/**
 *  Apply values to instance
 *
 *  First validates the values, and if all are found to be valid applies them on the instance of a class using its mappings.
 *
 *  @param values The values to be applied
 *  @param error  Error when invalid values are encountered
 *
 *  @return YES if all values are valid, NO otherwise
 */
- (BOOL)setValues:(NSDictionary *)values error:(NSError **)error;

#pragma mark - NSCoding support
/**
 *  Encodes an instance using mappings
 *
 *  @param aCoder The NSCoder object from the -[encodeWithCoder:] method
 */
- (void)encodeUsingMappingsWithCoder:(NSCoder *)aCoder;

/**
 *  Decodes an instance using mappings
 *
 *  The coding confirms to NSSecureCoding, so you may wish to return YES from -[ requiresSecureCoding] in your subclass.
 *
 *  @param aDecoder The NSCoder object from the -[initWithCoder:] method
 */
- (void)decodeUsingMappingsWithCoder:(NSCoder *)aDecoder;

#pragma mark - Dictionary representation

/**
 *  The keys that should be included in a dictionary representation
 *
 *  By default returns nil, which means that all external keys defined in the mappings of the class are included.
 *
 *  @return Array of NSString keys
 */
+ (NSArray *)dictionaryRepresentationKeys;

/**
 *  Creates a dictionary representation
 *
 *  The dictionary is created using the passed in array of keys. For classes not returning any mappings, the object is included as is. If a value is nil, or its reverse transformation fails, the key will be set to NSNull.
 *
 *  @param keys The keys to include in the dictionary, pass nil to include all
 *
 *  @return Dictionary representation of the object
 */
- (id)dictionaryRepresentationForKeys:(NSArray *)keys;

/**
 *  Creates a dictionary representation
 *
 *  The dictionary is created using the external keys as returned by +[dictionaryRepresentationKeys], or if that method returns nil those defined in the mappings of the class. For classes not returning any mappings, the object is included as is. If a value is nil, or its reverse transformation fails, the key will be set to NSNull.
 *
 *  @return Dictionary representation of the object
 */
- (id)dictionaryRepresentation;

@end
