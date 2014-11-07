<?php

/**
 * @file
 * The Drupal status implementation.   
 */

/**
 * Implementation of hook_drush_help().
 * @param
 *   A string with the help section (prepend with 'drush:')
 * @return
 *   A string with the help text for your command.
 */
function drupal_status_drush_help($section) {
  switch ($section) {
    case 'meta:drupal_status:title':
      return dt('Drupal Status');
    case 'drush:drupal-status':
      return dt('Provides a birds-eye view of the current Drupal installation status.');
      break;
  }
}

/**
 * Implementation of hook_drush_command().
 * @See drush_parse_command() for a list of recognized keys.
 * @return
 *   An associative array describing your command(s).
 */
function drupal_status_drush_command() {
  $items = array();

  $items['drupal-status'] = array(
    'examples' => array(
      'drush drupal-status' => dt('Prints the Drupal status report table.'),
    ),
  );
  return $items;
}

/**
 * Command callback, print Drupal status table. 
 */
function drush_drupal_status() {
   // Load .install files
  include_once DRUPAL_ROOT . '/includes/install.inc';
  drupal_load_updates();

  // Check run-time requirements and status information.
  $requirements = module_invoke_all('requirements', 'runtime');
  usort($requirements, '_system_sort_requirements');
  $header = array(
    dt('Severity'),
    dt('Title'),
    dt('Value'),
    dt('Description')
  );
  $rows = array();
  $rows[] = $header;

  foreach($requirements as $requirement) {
    $row = array();
      
    // Get severity.
    if (!array_key_exists('severity', $requirement) || $requirement['severity'] == 0) {
      $severity = dt('OK');   
    }
    else if($requirement['severity'] == -1) {
      $severity = dt('Info');   
    }
    else if($requirement['severity'] == 1) {
      $severity = dt('Warning');   
    }
    else if($requirement['severity'] == 2) {
      $severity = dt('Error');   
    }
    $value = strip_tags($requirement['value']);
       
    if (array_key_exists('description', $requirement)) {
      $description = preg_replace("#\<a.+href\=[\"|\'](.+)[\"|\'].*\>.*\<\/a\>#U","$1", $description);
      $description = strip_tags($requirement['description']);
    }
    else {
      $description =  ' ';
    }
      
    // Build rows.
    $row[] = $severity;
    $row[] = $requirement['title'];
    $row[] = strip_tags(preg_replace("#\<a.+href\=[\"|\'](.+)[\"|\'].*\>.*\<\/a\>#U","$1", $requirement['value']));
    $row[] = $description;
      
    array_push($rows, $row);
  }
  drush_print_table($rows, TRUE);
  drush_set_context('DRUSH_EXECUTION_COMPLETED', TRUE);
}
/** @} */ 
