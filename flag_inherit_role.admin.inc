<?php
/**
 * @file
 * Administrative page callbacks for the flag inherit role module.
 *
 * @ingroup flag inherit role
 */

/**
 * Implementations of flag inherit role settings form
 */
function flag_inherit_role_settings_form() {  
  $form = array();
  $roles = user_roles();
  // remove anonymous and authenticated user roles from list
  unset($roles[1]);
  unset($roles[2]);

  // Show checkboxes with roles that can be delegated if any.
  if (sizeOf($roles) > 0)
  $form['flag_inherit_role_roles'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles to be used when flagged'),
    '#options' => $roles,
    '#default_value' => variable_get('flag_inherit_role_roles', array()),
    '#description' => t('Choose roles'),
  );
  else
    $form[] = array('#value' => t('Please !link before you can use flag inherit role.', array('!link' => l('add additional roles', 'admin/user/roles'))) . '<br/>');
  
  // Get all the flag types from the system.
  $flags = array();
  foreach (flag_get_flags() as $flag) {
    if ($flag->content_type == 'user')
      $flags[$flag->fid] = $flag->title;
  }
  // List all Flag types
  if (sizeOf($flags) > 0)
  $form['flag_inherit_role_flag_type'] = array(
    '#type' => 'select',
    '#title' => t('Flag type'),
    '#options' => $flags,
    '#default_value' => variable_get('flag_inherit_role_flag_type', ''),
    '#description' => t('Choose Flag'),
  );
  else
    $form[] = array('#value' => t('Please !link before you can use flag inherit role.', array('!link' => l('add a user type flag', 'admin/build/flags/add'))) . '<br/>');

  return system_settings_form($form);
}