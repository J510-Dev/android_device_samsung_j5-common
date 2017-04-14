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
	std::string bootloader = property_get("ro.bootloader");

	if (bootloader.find("J500FN") == 0) {
		property_set("ro.build.product", "j5nlte");
		property_set("ro.build.description", "lineage_j5nlte-userdebug 7.1.1 NMF26V 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j5nlte/j5nlte:7.1.1/NMF26V/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j5nlte");
		property_set("ro.product.model", "SM-J500FN");
		gsm_lte_properties("10");
	}
	else if (bootloader.find("J500F") == 0) {
		property_set("ro.build.product", "j5lte");
		property_set("ro.build.description", "lineage_j5lte-userdebug 7.1.1 NMF26V 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j5lte/j5lte:7.1.1/NMF26V/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j5lte");
		property_set("ro.product.model", "SM-J500F");
		gsm_lte_properties("10");
	}
	else if (bootloader.find("J500H") == 0) {
		property_set("ro.build.product", "j53gxx");
		property_set("ro.build.description", "lineage_j53gxx-userdebug 7.1.1 NMF26V 4dae919457 test-keys");
		property_set("ro.build.fingerprint", "samsung/lineage_j53gxx/j53gxx:7.1.1/NMF26V/4dae919457:userdebug/test-keys");
		property_set("ro.product.device", "j53gxx");
		property_set("ro.product.model", "SM-J500H");
		property_set("persist.radio.rat_on", "combine");
		property_set("ro.telephony.default_network", "9");
	}

	std::string device = property_get("ro.product.device");
	INFO("Found bootloader id %s setting build properties for %s device\n", bootloader.c_str(), device.c_str());
}

void vendor_load_properties(void)
{
	/* set the device properties */
	init_target_properties();
}
