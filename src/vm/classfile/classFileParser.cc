//
// Created by pxcai on 2021/9/8.
//

#include "classFileParser.hh"

#define JAVA_CLASSFILE_MAGIC              0xCAFEBABE
#define JAVA_MIN_SUPPORTED_VERSION        45
#define JAVA_MAX_SUPPORTED_VERSION        52
#define JAVA_MAX_SUPPORTED_MINOR_VERSION  0

// Used for two backward compatibility reasons:
// - to check for new additions to the class file format in JDK1.5
// - to check for bug fixes in the format checker in JDK1.5
#define JAVA_1_5_VERSION                  49

// Used for backward compatibility reasons:
// - to check for javac bug fixes that happened after 1.5
// - also used as the max version when running in jdk6
#define JAVA_6_VERSION                    50

// Used for backward compatibility reasons:
// - to check NameAndType_info signatures more aggressively
#define JAVA_7_VERSION                    51

// Extension method support.
#define JAVA_8_VERSION                    52
