<?php
// $Id: $

function dragref_settings_form() {
  $vars = dragref_variable_get();
  $form['help'] = array(
    '#value' => print_r($vars, TRUE),
  );
  
  // Create some options out of content types.
  $types = content_types();
  foreach ($types as $machine => $type) {
    $options[$machine] = $type['name'];
  }
  
  // Choose the parent content type.
  $form['dragref_parent'] = array(
    '#type' => 'radios', 
    '#title' => t('Choose your parent content type'),
    '#options' => $options, 
    '#default_value' => variable_get('dragref_parent', NULL),
  );
  
  // Choose the child content type.
  $form['dragref_child'] = array(
    '#type' => 'radios', 
    '#title' => t('Choose your child content type'),
    '#options' => $options, 
    '#default_value' => variable_get('dragref_child', NULL),
  );

  $form = system_settings_form($form);
  array_unshift($form['#submit'], 'dragref_settings_form_submit');

  return $form;
}


function dragref_settings_form_submit($form, &$form_state) {
  $child = $form_state['values']['dragref_child'];
  if (!empty($child)) {
    $type = content_types($child);
    $fields = $type['fields'];
    foreach ($fields as $field) {
      if ($field['type'] == 'nodereference') {
        variable_set('dragref_child_field', $field['field_name']);
      }
    }
  }
}

// @todo: check to make sure that the child noderef references the parent
function dragref_settings_form_validate($form, &$form_state) {
  // Ensure the parent child are not the same.
  $parent = $form_state['values']['dragref_parent'];
  $child = $form_state['values']['dragref_child'];
  if ($parent == $child) {
    $msg = t('You cannot have the same type for parent and child.');
  }
  else {
    // Ensure the child content type has a nodereference_url widget.
    $type = content_types($child);
    $child_fields = $type['fields'];
    if (empty($child_fields)) {
      $msg = t('You must have a nodereference field.');
    }
    else {
      foreach ($child_fields as $field) {        
        if ($field['type'] != 'nodereference' || $field['widget']['type'] !== 'nodereference_url') {
          $msg = t('You child type must be a nodereference field using the nodereference_url widget.');
        }
      }
    }
  }
  if ($msg) {
    form_set_error($child, $msg);
  }
}
