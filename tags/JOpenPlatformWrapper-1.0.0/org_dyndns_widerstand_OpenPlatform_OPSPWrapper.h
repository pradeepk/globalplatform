/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_dyndns_widerstand_OpenPlatform_OPSPWrapper */

#ifndef _Included_org_dyndns_widerstand_OpenPlatform_OPSPWrapper
#define _Included_org_dyndns_widerstand_OpenPlatform_OPSPWrapper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getLastOpenSSLErrorCode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getLastOpenSSLErrorCode
  (JNIEnv *, jclass);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    establishContext
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_establishContext
  (JNIEnv *, jclass);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    releaseContext
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_releaseContext
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    listReaders
 * Signature: (J)[Ljava/lang/String;
 */
JNIEXPORT jobjectArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_listReaders
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    cardConnect
 * Signature: (JLjava/lang/String;J)J
 */
JNIEXPORT jlong JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_cardConnect
  (JNIEnv *, jclass, jlong, jstring, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    cardDisconnect
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_cardDisconnect
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    selectApplication
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[B)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_selectApplication
  (JNIEnv *, jclass, jlong, jobject, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getStatus
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;B)[Lorg/dyndns/widerstand/OpenPlatform/OPSPApplicationData;
 */
JNIEXPORT jobjectArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getStatus
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    setStatus
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;B[BB)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_setStatus
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyteArray, jbyte);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    stringifyError
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_stringifyError
  (JNIEnv *, jclass, jint);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getCardStatus
 * Signature: (J)Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getCardStatus
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    mutualAuthentication
 * Signature: (J[B[BBBLorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;B)Lorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_mutualAuthentication
  (JNIEnv *, jclass, jlong, jbyteArray, jbyteArray, jbyte, jbyte, jobject, jbyte);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getData
 * Signature: (J[BLorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getData
  (JNIEnv *, jclass, jlong, jbyteArray, jobject, jobject);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    putData
 * Signature: (J[B[BLorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_putData
  (JNIEnv *, jclass, jlong, jbyteArray, jbyteArray, jobject, jobject);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    pinChange
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;B[B[B)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_pinChange
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    put3desKey
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;BBB[B[B)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_put3desKey
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyte, jbyte, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    putRsaKey
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;BBBLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_putRsaKey
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyte, jbyte, jstring, jstring);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    putSecureChannelKeys
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;BB[B[B[B[B)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_putSecureChannelKeys
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyte, jbyteArray, jbyteArray, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    deleteKey
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;BB)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_deleteKey
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyte);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getKeyInformationTemplates
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;B)[Lorg/dyndns/widerstand/OpenPlatform/OPSPKeyInformation;
 */
JNIEXPORT jobjectArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getKeyInformationTemplates
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    deleteApplet
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[[B)[Lorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;
 */
JNIEXPORT jobjectArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_deleteApplet
  (JNIEnv *, jclass, jlong, jobject, jobject, jobjectArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    installForLoad
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[B[B[B[BJJJ)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_installForLoad
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyteArray, jbyteArray, jbyteArray, jbyteArray, jlong, jlong, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getLoadTokenSignatureData
 * Signature: ([B[B[BJJJ)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getLoadTokenSignatureData
  (JNIEnv *, jclass, jbyteArray, jbyteArray, jbyteArray, jlong, jlong, jlong);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    getInstallTokenSignatureData
 * Signature: (B[B[B[BBJJ[B)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_getInstallTokenSignatureData
  (JNIEnv *, jclass, jbyte, jbyteArray, jbyteArray, jbyteArray, jbyte, jlong, jlong, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    calculateLoadToken
 * Signature: ([B[B[BJJJLjava/lang/String;Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_calculateLoadToken
  (JNIEnv *, jclass, jbyteArray, jbyteArray, jbyteArray, jlong, jlong, jlong, jstring, jstring);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    calculateInstallToken
 * Signature: (B[B[B[BBJJ[BLjava/lang/String;Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_calculateInstallToken
  (JNIEnv *, jclass, jbyte, jbyteArray, jbyteArray, jbyteArray, jbyte, jlong, jlong, jbyteArray, jstring, jstring);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    calculateLoadFileDAP
 * Signature: ([Lorg/dyndns/widerstand/OpenPlatform/OPSPDAPBlock;Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_calculateLoadFileDAP
  (JNIEnv *, jclass, jobjectArray, jstring);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    loadApplet
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[Lorg/dyndns/widerstand/OpenPlatform/OPSPDAPBlock;Ljava/lang/String;)Lorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_loadApplet
  (JNIEnv *, jclass, jlong, jobject, jobject, jobjectArray, jstring);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    installForInstall
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[B[B[BBJJ[B[B)Lorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_installForInstall
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyteArray, jbyteArray, jbyteArray, jbyte, jlong, jlong, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    installForMakeSelectable
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[BB[B)Lorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_installForMakeSelectable
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyteArray, jbyte, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    installForInstallAndMakeSelectable
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;[B[B[BBJJ[B[B)Lorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_installForInstallAndMakeSelectable
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyteArray, jbyteArray, jbyteArray, jbyte, jlong, jlong, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    putDelegatedManagementKeys
 * Signature: (JLorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;BBLjava/lang/String;Ljava/lang/String;[B[B)V
 */
JNIEXPORT void JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_putDelegatedManagementKeys
  (JNIEnv *, jclass, jlong, jobject, jobject, jbyte, jbyte, jstring, jstring, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    sendAPDU
 * Signature: (J[BLorg/dyndns/widerstand/OpenPlatform/OPSPCardConnectionInfo;Lorg/dyndns/widerstand/OpenPlatform/OPSPSecurityInfo;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_sendAPDU
  (JNIEnv *, jclass, jlong, jbyteArray, jobject, jobject);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    calculate3desDAP
 * Signature: ([BLjava/lang/String;[B)Lorg/dyndns/widerstand/OpenPlatform/OPSPDAPBlock;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_calculate3desDAP
  (JNIEnv *, jclass, jbyteArray, jstring, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    calculateRsaDAP
 * Signature: ([BLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Lorg/dyndns/widerstand/OpenPlatform/OPSPDAPBlock;
 */
JNIEXPORT jobject JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_calculateRsaDAP
  (JNIEnv *, jclass, jbyteArray, jstring, jstring, jstring);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    validateDeleteReceipt
 * Signature: (J[B[BLorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_validateDeleteReceipt
  (JNIEnv *, jclass, jlong, jbyteArray, jbyteArray, jobject, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    validateInstallReceipt
 * Signature: (J[B[BLorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_validateInstallReceipt
  (JNIEnv *, jclass, jlong, jbyteArray, jbyteArray, jobject, jbyteArray, jbyteArray);

/*
 * Class:     org_dyndns_widerstand_OpenPlatform_OPSPWrapper
 * Method:    validateLoadReceipt
 * Signature: (J[B[BLorg/dyndns/widerstand/OpenPlatform/OPSPReceiptData;[B[B)Z
 */
JNIEXPORT jboolean JNICALL Java_org_dyndns_widerstand_OpenPlatform_OPSPWrapper_validateLoadReceipt
  (JNIEnv *, jclass, jlong, jbyteArray, jbyteArray, jobject, jbyteArray, jbyteArray);

#ifdef __cplusplus
}
#endif
#endif
