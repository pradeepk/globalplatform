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
#include <GlobalPlatform/GlobalPlatform.h>

/**
* Maximum length of the reader name.
*/ 
#define READERNAMELEN 256

/**
* Reader number to conenct to.
*/ 
#define READERNUM 3

/**
* Maximum buffer size for reader names.
*/ 
#define BUFLEN 2048

/**
* Global card context for the test.
*/
static OPGP_CARDCONTEXT cardContext;

/**
* Global card info for the test.
*/
static OPGP_CARD_INFO cardInfo;

/**
* Readername for the test.
*/
static TCHAR readerName[READERNAMELEN + 1];

static void internal_connect_card() {
	LONG rv;
	rv = card_connect (cardContext, readerName,
		&cardInfo, (OPGP_CARD_PROTOCOL_T0|OPGP_CARD_PROTOCOL_T1));
	if (rv != OPGP_ERROR_SUCCESS) {
		fail("Could not connect to card: %s", stringify_error(rv));
	}
	_tprintf(_T("Connected to reader %s\n"), readerName);
}

static void internal_establish_context() {
	LONG rv;
	rv = establish_context(&cardContext);
	if (rv != OPGP_ERROR_SUCCESS) {
		fail("Could not establish context: %s", stringify_error(rv));
	}
	_tprintf(_T("Using card context %08X\n"), cardContext);
}

static void internal_list_readers() {
	LONG rv;
	TCHAR buf[BUFLEN + 1];
	int j,k;
	DWORD readerStrLen = BUFLEN;
	rv = list_readers (cardContext, buf, &readerStrLen);
	if (rv != OPGP_ERROR_SUCCESS) {
		fail("Could not list readers: %s", stringify_error(rv));
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

/**
* Tests the connection to the card.
*/
START_TEST(test_connect_card) 
{
	internal_establish_context();
	internal_list_readers();
	internal_connect_card();
}
END_TEST

/**
* Tests the listing of readers.
*/
START_TEST (test_list_readers)
{
	internal_establish_context();
	internal_list_readers();
}
END_TEST

/**
* Tests the context establishment.
*/
START_TEST (test_establish_context)
{
	internal_establish_context();
}
END_TEST

/**
* Tests the key derivation according to gemXpresso scheme.
*/
START_TEST (test_GemXpressoPro_create_daughter_keys)
{
	internal_connect();
	LONG rv;
	BYTE motherKey[] = {0x4D, 0xA5, 0xFC, 0x18, 0xA4, 0x6F, 0x8A, 0x02, 0x05, 0xC7, 0x7C, 0x37, 0x3B, 0x58, 0x2A, 0x1F};
	BYTE S_ENC[16], S_MAC[16], DEK[16];
	int i;
	rv = GemXpressoPro_create_daughter_keys(cardInfo, (PBYTE)GP211_CARD_MANAGER_AID_ALT1, sizeof(GP211_CARD_MANAGER_AID_ALT1), motherKey,
		S_ENC, S_MAC, DEK);
	if (rv != OPGP_ERROR_SUCCESS) {
		fail("Derivation of keys failed:", stringify_error(rv));
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
	tcase_add_test (tc_core, test_GemXpressoPro_create_daughter_keys);
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
