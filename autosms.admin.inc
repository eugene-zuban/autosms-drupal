<?php

/**
 * @file
 * Administration page callbacks for the autosms module.
 */

/**
 * Form builder. Configure annotations.
 *
 * @ingroup forms
 * @see system_settings_form().
 */
function autosms_admin_settings() {
  $start = 0;
  $end = 24 * 60 + 0;

  for ($crontime = $start; $crontime <= $end; $crontime += 60) {
    $minute = $crontime % 60;
    $hour = ($crontime - $minute) / 60;
    $auto_time = sprintf('%02d:%02d', $hour, $minute);
    $options[$auto_time] = $auto_time;
  }

  $form['autosms_cron_time'] = array(
    '#type' => 'select',
    '#title' => t('SMS sending time'),
    '#options' => $options,
    '#default_value' => variable_get('autosms_cron_time', '00:00'),
    '#description' => t('Select time when SMS wil be sending.'),
  );

  $options_sh = array(
    '1' => t('Every day'),
    '2' => t('Every other day'),
    '3' => t('Every 3 days'),
  );

  $form['autosms_shedule_count'] = array(
    '#type' => 'select',
    '#title' => t('Frequency of sending a SMS'),
    '#options' => $options_sh,
    '#default_value' => variable_get('autosms_shedule_count', array('1')),
    '#description' => t('Specify how often do you want to send a SMS'),
  );

  $form['autosms_sender_name'] = array(
    '#title' => t('Senders name'),
    '#type' => 'textfield',
    '#description' => t('The senders name, that approved by the SMS Gateway'),
    '#default_value' => variable_get('autosms_sender_name', ''),
    '#size' => 20,
    '#weight' => -10,
  );

  $form['autosms_gw_server'] = array(
    '#title' => t('SMS GW Address'),
    '#type' => 'textfield',
    '#description' => t('MySQL address'),
    '#default_value' => variable_get('autosms_gw_server', ''),
    '#size' => 30,
    '#weight' => 10,
  );

  $form['autosms_gw_db'] = array(
    '#title' => t('Data Base'),
    '#type' => 'textfield',
    '#description' => t('Gateways Data Base'),
    '#default_value' => variable_get('autosms_gw_db', ''),
    '#size' => 30,
    '#weight' => 11,
  );

  $form['autosms_gw_db_table'] = array(
    '#title' => t('DB Table'),
    '#type' => 'textfield',
    '#description' => t('SMS Gateway DB Table'),
    '#default_value' => variable_get('autosms_gw_db_table', ''),
    '#size' => 30,
    '#weight' => 12,
  );

  $form['autosms_gw_login'] = array(
    '#title' => t('DB Username'),
    '#type' => 'textfield',
    '#description' => t('DB Username for SMS GW'),
    '#default_value' => variable_get('autosms_gw_login', ''),
    '#size' => 30,
    '#weight' => 13,
  );

  $form['autosms_gw_pass'] = array(
    '#title' => t('DB Password'),
    '#type' => 'textfield',
    '#description' => t('DB Password for SMS GW'),
    '#default_value' => variable_get('autosms_gw_pass', ''),
    '#size' => 30,
    '#weight' => 14,
  );

  $options = array(
    'testing' => t('Testing mode'),
  );
  $form['autosms_test_mode'] = array(
    '#title' => t('Testing mode'),
    '#type' => 'checkboxes',
    '#description' => t('Check for enabling the testing mode (the time field will be ignored).'),
    '#options' => $options,
    '#default_value' => variable_get('autosms_test_mode', ''),
    '#weight' => 25,
  );

  $form['#submit'][] = 'autosms_admin_settings_submit';
  return system_settings_form($form);
}

/**
 * Process autosms settings submission.
 */
function autosms_admin_settings_submit($form, $form_state) {
  variable_set('autosms_cron_time', $form_state['values']['autosms_cron_time']);
  variable_set('autosms_shedule_count', $form_state['values']['autosms_shedule_count']);
  variable_set('autosms_sender_name', $form_state['values']['autosms_sender_name']);
  variable_set('autosms_test_mode', $form_state['values']['autosms_test_mode']);
}

/**
 * Validate the form.
 */
function autosms_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['autosms_sender_name'] == '') {
    form_set_error('autosms_sender_name', t('Sender cant be empty.'));
  }
}