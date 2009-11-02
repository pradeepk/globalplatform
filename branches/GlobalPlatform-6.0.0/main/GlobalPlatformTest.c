/*  Copyright (c) 2008, Karsten Ohme
 *  This file is part of GlobalPlatform.
 *
 *  GlobalPlatform is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GlobalPlatform is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with GlobalPlatform.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <check.h>
#include <stdlib.h>
#include "GlobalPlatform/GlobalPlatform.h"
#include <stdio.h>
#include <string.h>

/**
* Maximum length of the reader name.
*/
#define READERNAMELEN 256

/**
* Reader number to connect to.
*/
#define READERNUM 3

/**
* Maximum buffer size for reader names.
*/
#define BUFLEN 2048

/**
* Global card context for the test.
*/
static OPGP_CARD_CONTEXT cardContext;

/**
* Global card info for the test.
*/
static OPGP_CARD_INFO cardInfo;

/**
* Readername for the test.
*/
static TCHAR readerName[READERNAMELEN + 1];

static void internal_disconnect_card() {
	OPGP_ERROR_STATUS status;
	status = OPGP_card_disconnect(cardContext, &cardInfo);
	if (OPGP_ERROR_CHECK(status)) {
		fail("Could not connect to card: %s", status.errorMessage);
	}
	fail_unless(cardInfo.librarySpecific == NULL, "Library specific data must be NULL after disconnecting.");
	_tprintf(_T("Disconnected from reader %s\n"), readerName);
}

static void internal_release_context() {
	OPGP_ERROR_STATUS status;
	status = OPGP_release_context(&cardContext);
	if (OPGP_ERROR_CHECK(status)) {
		fail("Could not connect to card: %s", status.errorMessage);
	}
	fail_unless(cardContext.libraryHandle == NULL, "Library handle must be NULL after releasing.");
	fail_unless(cardContext.librarySpecific == NULL, "Library specific data must be NULL after releasing.");
}

static void internal_connect_card() {
	OPGP_ERROR_STATUS status;
	status = OPGP_card_connect (cardContext, readerName,
		&cardInfo, (OPGP_CARD_PROTOCOL_T0|OPGP_CARD_PROTOCOL_T1));
	if (OPGP_ERROR_CHECK(status)) {
		fail("Could not connect to card: %s", status.errorMessage);
	}
	_tprintf(_T("Connected to reader %s\n"), readerName);
}

static void internal_establish_context() {
	OPGP_ERROR_STATUS status;
	_tcsncpy(cardContext.libraryName, _T("pcscconnectionplugin"), sizeof(cardContext.libraryName));
	status = OPGP_establish_context(&cardContext);
	if (OPGP_ERROR_CHECK(status)) {
		fail("Could not establish context: %s", status.errorMessage);
	}
}

static void internal_list_readers() {
	OPGP_ERROR_STATUS status;
	TCHAR buf[BUFLEN + 1];
	int j,k;
	DWORD readerStrLen = BUFLEN;
	status = OPGP_list_readers (cardContext, buf, &readerStrLen);
	if (OPGP_ERROR_CHECK(status)) {
		fail("Could not list readers: %s", status.errorMessage);
	}
	// we choose the READERNUM reader
	for (j=0; j<(int)readerStrLen;) {
		/* Check for end of readers */
		if (buf[j] == _T('\0')) {
			break;
		}
		_tcsncpy(readerName, buf+j, READERNAMELEN+1);
		if (j == READERNUM) {
			break;
		}
		j+=(int)_tcslen(buf+j)+1;
	}
	readerName[READERNAMELEN] = _T('\0');
	if (_tcslen(readerName) == 0) {
		fail("No reader found.");
	}
	_tprintf(_T("Using reader %s\n"), readerName);
}

static void internal_connect() {
	internal_establish_context();
	internal_list_readers();
	internal_connect_card();
}

static void internal_disconnect() {
	internal_disconnect_card();
	internal_release_context();
}

/**
* Tests the connection to the card.
*/
START_TEST(test_connect_card)
{
	internal_establish_context();
	internal_list_readers();
	internal_connect_card();
	internal_disconnect_card();
	internal_release_context();
}
END_TEST

/**
* Tests the listing of readers.
*/
START_TEST (test_list_readers)
{
	internal_establish_context();
	internal_list_readers();
	internal_release_context();
}
END_TEST

/**
* Tests the context establishment.
*/
START_TEST (test_establish_context)
{
	internal_establish_context();
	internal_release_context();
}
END_TEST

/**
* Tests the key derivation according to gemXpresso scheme.
*/
START_TEST (test_OPGP_VISA2_derive_keys)
{
	internal_connect();
	OPGP_ERROR_STATUS status;
	BYTE motherKey[] = {0x4D, 0xA5, 0xFC, 0x18, 0xA4, 0x6F, 0x8A, 0x02, 0x05, 0xC7, 0x7C, 0x37, 0x3B, 0x58, 0x2A, 0x1F};
	BYTE S_ENC[16], S_MAC[16], DEK[16];
	int i;
	status = OPGP_VISA2_derive_keys(cardContext, cardInfo, (PBYTE)GP211_CARD_MANAGER_AID_ALT1, sizeof(GP211_CARD_MANAGER_AID_ALT1), motherKey,
		S_ENC, S_MAC, DEK);
	if (OPGP_ERROR_CHECK(status)) {
		fail("Derivation of keys failed:", status.errorMessage);
	}
	for (i = 0; i<16; i++) {
		printf("%02X", S_ENC[i]);
	}
	printf("\n");
	for (i = 0; i<16; i++) {
		printf("%02X", S_MAC[i]);
	}
	printf("\n");
	for (i = 0; i<16; i++) {
		printf("%02X", DEK[i]);
	}
	printf("\n");
	internal_disconnect();
}
END_TEST



Suite * GlobalPlatform_suite (void)
{


	Suite *s = suite_create ("GlobalPlatform");
	/* Core test case */
	TCase *tc_core = tcase_create ("Core");
	tcase_add_test (tc_core, test_establish_context);
	tcase_add_test (tc_core, test_list_readers);
	tcase_add_test (tc_core, test_connect_card);
	tcase_add_test (tc_core, test_OPGP_VISA2_derive_keys);
	suite_add_tcase (s, tc_core);

	return s;
}

int main (void)
{
	int number_failed;
	Suite *s = GlobalPlatform_suite ();
	SRunner *sr = srunner_create (s);
	srunner_run_all (sr, CK_NORMAL);
	number_failed = srunner_ntests_failed (sr);
	srunner_free (sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
