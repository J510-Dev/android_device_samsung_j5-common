/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above
	  copyright notice, this list of conditions and the following
	  disclaimer in the documentation and/or other materials provided
	  with the distribution.
	* Neither the name of The Linux Foundation nor the names of its
	  contributors may be used to endorse or promote products derived
	  from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

void cdma_properties(char const *operator_alpha,
		char const *operator_numeric,
		char const *default_network)
{
	/* Dynamic CDMA Properties */
	property_set("ro.cdma.home.operator.alpha", operator_alpha);
	property_set("ro.cdma.home.operator.numeric", operator_numeric);
	property_set("ro.telephony.default_network", default_network);

	/* Static CDMA Properties */
	property_set("ril.subscription.types", "NV,RUIM");
	property_set("ro.telephony.default_cdma_sub", "0");
	property_set("ro.telephony.get_imsi_from_sim", "true");
	property_set("ro.telephony.ril.config", "newDriverCallU,newDialCode");
	property_set("telephony.lteOnCdmaDevice", "1");
}

void gsm_lte_properties(char const * default_network)
{
	property_set("persist.radio.lte_vrte_ltd", "1");
	property_set("telephony.lteOnCdmaDevice", "0");
	property_set("ro.telephony.default_network", default_network);
}

void init_target_properties(void)
{
	char bootloader[PROP_VALUE_MAX];
	char device[PROP_VALUE_MAX];

	/* get the bootloader string */
	property_get("ro.bootloader", bootloader);

	if (strstr(bootloader,"J500FN")) {
		property_set("ro.build.product", "j5nltexx");
		property_set("ro.build.description", "lineage_j5nltexx-userdebug 7.1.1 NMF26V 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j5nltexx/j5nltexx:7.1.1/NMF26V/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j5nltexx");
		property_set("ro.product.model", "SM-J500FN");
		gsm_lte_properties("10");
	}
	else if (strstr(bootloader,"J500F")) {
		property_set("ro.build.product", "j5ltexx");
		property_set("ro.build.description", "lineage_j5ltexx-userdebug 7.1.1 NMF26V 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j5ltexx/j5ltexx:7.1.1/NMF26V/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j5ltexx");
		property_set("ro.product.model", "SM-J500F");
		gsm_lte_properties("10");
	}
	else if (strstr(bootloader,"J510FN")) {
		property_set("ro.build.product", "j5xnlte");
		property_set("ro.build.description", "lineage_j5xnlte-userdebug 6.0.1 MOB31K 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j5xnlte/j5xnlte:6.0.1/MOB31K/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j5xnlte");
		property_set("ro.product.model", "SM-J510FN");
		property_set("persist.radio.rat_on", "combine");
		property_set("ro.telephony.default_network", "9");
	}
	else if (strstr(bootloader,"J510MN")) {
		property_set("ro.build.product", "j5xnlte);
		property_set("ro.build.description", "lineage_j5xnlte-userdebug 6.0.1 MOB31K 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j5xnlte/j5xnlte:6.0.1/MOB31K/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j5xnlte");
		property_set("ro.product.model", "SM-J510MN");
		property_set("persist.radio.rat_on", "combine");
		property_set("ro.telephony.default_network", "9");
	}


	property_get("ro.product.device", device);
	INFO("Found bootloader id %s setting build properties for %s device\n", bootloader, device);
}

void vendor_load_properties(void)
{
	/* set the device properties */
	init_target_properties();
}
