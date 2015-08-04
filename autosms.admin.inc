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
    '#description' => t('Укажите время, по достижению которого будет запущен планировщик и выполнена рассылка SMS сообщений.'),
  );

  $options_sh = array(
    '1' => t('Каждый день'),
    '2' => t('Через день'),
    '3' => t('Каждые 3 дня'),
  );

  $form['autosms_shedule_count'] = array(
    '#type' => 'select',
    '#title' => t('Периодичность отправки SMS'),
    '#options' => $options_sh,
    '#default_value' => variable_get('autosms_shedule_count', array('1')),
    '#description' => t('Укажите как часто необходимо отправлять SMS'),
  );

  $form['autosms_sender_name'] = array(
    '#title' => t('Имя отправителя'),
    '#type' => 'textfield',
    '#description' => t('Введите имя отправителя сообщений, которое утверждено сервисом шлюза SMS'),
    '#default_value' => variable_get('autosms_sender_name', 'Ukrcity'),
    '#size' => 20,
    '#weight' => -10,
  );

  $form['autosms_gw_server'] = array(
    '#title' => t('Адрес SMS шлюза'),
    '#type' => 'textfield',
    '#description' => t('Введите адрес MySQL сервера'),
    '#default_value' => variable_get('autosms_gw_server', ''),
    '#size' => 30,
    '#weight' => 10,
  );

  $form['autosms_gw_db'] = array(
    '#title' => t('База данных'),
    '#type' => 'textfield',
    '#description' => t('Введите имя базы данных шлюза'),
    '#default_value' => variable_get('autosms_gw_db', ''),
    '#size' => 30,
    '#weight' => 11,
  );

  $form['autosms_gw_db_table'] = array(
    '#title' => t('Таблица данных'),
    '#type' => 'textfield',
    '#description' => t('Введите имя таблицы в базе данных шлюза'),
    '#default_value' => variable_get('autosms_gw_db_table', ''),
    '#size' => 30,
    '#weight' => 12,
  );

  $form['autosms_gw_login'] = array(
    '#title' => t('Логин для подключения'),
    '#type' => 'textfield',
    '#description' => t('Введите логин для подключения к БД'),
    '#default_value' => variable_get('autosms_gw_login', ''),
    '#size' => 30,
    '#weight' => 13,
  );

  $form['autosms_gw_pass'] = array(
    '#title' => t('Пароль для подключения'),
    '#type' => 'textfield',
    '#description' => t('Введите пароль для подключения к БД'),
    '#default_value' => variable_get('autosms_gw_pass', ''),
    '#size' => 30,
    '#weight' => 14,
  );

  $options = array(
    'testing' => t('Тестовый режим'),
  );
  $form['autosms_test_mode'] = array(
    '#title' => t('Режим тестирования'),
    '#type' => 'checkboxes',
    '#description' => (t('Отметьте данное поле, если необходимо протестировать работу модуля (игнорируется поле время).')),
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
    form_set_error('autosms_sender_name', t('Введите корректное имя отправителя'));
  }
}