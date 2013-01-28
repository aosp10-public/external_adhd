/* Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef _CRAS_ALSA_UCM_H
#define _CRAS_ALSA_UCM_H

#include <alsa/asoundlib.h>
#include <alsa/use-case.h>

#include "cras_types.h"

/* Helpers to access UCM configuration for a card if any is provided.
 * This configuration can specify how to enable or disable certain inputs and
 * outputs on the card.
 */

/* Creates a snd_use_case_mgr_t instance for the given card name if there is a
 * matching ucm configuration.  It there is a matching UCM config, then it will
 * be configured to the default state.
 *
 * Args:
 *    name - Name of the card to match against the UCM card list.
 * Returns:
 *    A pointer to the use case manager if found, otherwise NULL.  The pointer
 *    must later be freed with snd_use_case_mgr_close().
 */
snd_use_case_mgr_t *ucm_create(const char *name);

/* Destroys a snd_use_case_mgr_t that was returned from ucm_create.
 * Args:
 *    alsa_ucm - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 */
void ucm_destroy(snd_use_case_mgr_t *mgr);

/* Enables or disables a UCM device.  First checks if the device is already
 * enabled or disabled.
 * Args:
 *    alsa_ucm - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 *    dev - The ucm device to enable of disable.
 *    enable - Enable device if non-zero.
 * Returns:
 *    0 on success or negative error code on failure.
 */
int ucm_set_enabled(snd_use_case_mgr_t *mgr, const char *dev, int enable);

/* Gets the capture control name which associated with given ucm device.
 * Args:
 *    mgr - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 *    ucm_dev - The ucm device to get capture control for.
 * Returns:
 *    A pointer to the allocated string containing the name of the capture
 *    control, or NULL if no capture control is found.
 */
char *ucm_get_cap_control(snd_use_case_mgr_t *mgr, const char *ucm_dev);

/* Gets the name of the ucm device for the given jack name.
 * Args:
 *    mgr - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 *    jack - The name of the jack to search for.
 * Rreturns:
 *    A pointer to the allocated string containing the name of the device, or
 *    NULL if no device is found.
 */
char *ucm_get_dev_for_jack(snd_use_case_mgr_t *mgr, const char *jack);

/* If there is an EDID file variable specified for dev, return it.  The EDID
 * file will be used for HDMI devices so supported audio formats can be checked.
 * Args:
 *    mgr - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 *    dev - The device to check for an EDID file.
 * Returns:
 *    A string containing the name of the edid file on Success (Must be freed
 *    later).  NULL if none found.
 */
const char *ucm_get_edid_file_for_dev(snd_use_case_mgr_t *mgr, const char *dev);

/* Gets the dsp name which is associated with the given ucm device.
 * Args:
 *    mgr - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 *    ucm_dev - The ucm device to get dsp name for.
 *    direction - playback(CRAS_STREAM_OUTPUT) or capture(CRAS_STREAM_INPUT).
 * Returns:
 *    A pointer to the allocated string containing the dsp name, or NULL if no
 *    dsp name is found.
 */
const char *ucm_get_dsp_name(snd_use_case_mgr_t *mgr, const char *ucm_dev,
			      int direction);

/* Gets the default dsp name.
 * Args:
 *    mgr - The snd_use_case_mgr_t pointer returned from alsa_ucm_create.
 *    direction - playback(CRAS_STREAM_OUTPUT) or capture(CRAS_STREAM_INPUT).
 * Returns:
 *    A pointer to the allocated string containing the default dsp name, or
 *    NULL if no default dsp name is found.
 */
const char *ucm_get_dsp_name_default(snd_use_case_mgr_t *mgr, int direction);

#endif /* _CRAS_ALSA_UCM_H */
