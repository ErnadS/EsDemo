include(keyboard/keyboard.pri)

SOURCES += gui\widget\runtime_widget_es.cpp \
           gui\widget\information_widget.cpp \
           gui\widget\brightness_widget.cpp \
           gui\widget\navigation_widget.cpp \
           gui\widget\background_widget.cpp \
           gui\widget\button.cpp \
           gui\widget\display_alive_widget.cpp \
           gui\widget\title_widget.cpp \
           gui\widget\scalable_widget.cpp \
           gui\navigation_controller.cpp \
           gui\widget\runtime_widget_a.cpp \
           gui\widget\runtime_widget_b.cpp \
           gui\widget\runtime_widget_c.cpp \
           gui\widget\runtime_widget_d.cpp \
           gui\widget\runtime_widget_e.cpp \
           gui\widget\runtime_widget_dl1.cpp \
           gui\widget\runtime_widget.cpp \
           gui\widget\transparent_info_button.cpp \
           gui\widget\system_widget.cpp \
           gui\widget\system_widget_container.cpp \
           gui\widget\dl1_runtime_widget_b.cpp \
           gui\widget\es_runtime_widget_b.cpp \
           gui\widget\boat_button.cpp \
           gui\widget\item_widget.cpp \
           gui\widget\selectable_item_widget.cpp \
           gui\widget\item_widget_container.cpp \
           gui\widget\selectable_item_widget_container.cpp \
           gui\widget\selectable_enum_item_widget.cpp \
           gui\widget\selectable_int_item_widget.cpp \
           gui\widget\selectable_float_item_widget.cpp \
           gui\widget\selectable_string_item_widget.cpp \
           gui\widget\selectable_ip_item_widget.cpp \
           gui\widget\selectable_bool_item_widget.cpp \
           gui\widget\validator.cpp \
           gui\widget\arrow_widget.cpp \
           gui\widget\horizontal_item_widget.cpp \
           gui\widget\horizontal_item_widget_container.cpp \
           gui\widget\up_down_widget.cpp \
           gui\widget\leg_button.cpp \
           gui\widget\calibration_graph_widget.cpp \
           gui\screen\base_screen.cpp \
           gui\screen\runtime_screen.cpp \
           gui\screen\setup_menu_screen.cpp \
           gui\screen\boat_menu_screen.cpp \
           gui\screen\es_runtime_screen.cpp \
           gui\screen\setup_screen.cpp \
           gui\screen\multi_setup_screen.cpp \
           gui\screen\base_runtime_setup_screen.cpp \
           gui\screen\dl2_runtime_a_setup_screen.cpp \
           gui\screen\dl2_runtime_b_setup_screen.cpp \
           gui\screen\dl2_runtime_c_setup_screen.cpp \
           gui\screen\dl2_runtime_d_setup_screen.cpp \
           gui\screen\dl2_runtime_e_setup_screen.cpp \
           gui\screen\dl2_runtime_setup_screen.cpp \
           gui\screen\dl2_calibration_status_setup_screen.cpp \
           gui\screen\dl2_calibration_inst_angle_setup_screen.cpp \
           gui\screen\dl2_calibration_speed_setup_screen.cpp \
           gui\screen\dl2_calibration_speed_manual_gps_setup_screen.cpp \
           gui\screen\dl2_calibration_speed_manual_setup_screen.cpp \
           gui\screen\dl2_calibration_speed_sea_setup_screen.cpp \
           gui\screen\dl2_calibration_speed_auto_setup_screen.cpp \
           gui\screen\dl2_calibration_tilt_setup_screen.cpp \
           gui\screen\dl2_calibration_temp_setup_screen.cpp \
           gui\screen\dl2_calibration_setup_screen.cpp \
           gui\screen\dl2_alert_setup_screen.cpp \
           gui\screen\dl2_diagnostic_setup_screen.cpp \
           gui\screen\dl2_setup_screen.cpp \
           gui\screen\dl2_setup_setup_screen.cpp \
           gui\screen\dl2_setup_options_screen.cpp \
           gui\screen\dl2_communication_setup_screen.cpp \
           gui\screen\dl2_aux_setup_screen.cpp \
           gui\screen\dl2_jb70_setup_screen.cpp \
           gui\screen\es_runtime_a_setup_screen.cpp \
           gui\screen\es_runtime_b_setup_screen.cpp \
           gui\screen\es_runtime_setup_screen.cpp \
           gui\screen\es_alert_setup_screen.cpp \
           gui\screen\es_diagnostic_setup_screen.cpp \
           gui\screen\es_setup_screen.cpp \
           gui\screen\es_communication_setup_screen.cpp \
           gui\screen\es_aux_setup_screen.cpp \
           gui\screen\es_history_setup_screen.cpp \
           gui\screen\es_jb70_setup_screen.cpp \
           gui\screen\dl1_runtime_a_setup_screen.cpp \
           gui\screen\dl1_runtime_b_setup_screen.cpp \
           gui\screen\dl1_runtime_setup_screen.cpp \
           gui\screen\dl1_calibration_setup_screen.cpp \
           gui\screen\dl1_alert_setup_screen.cpp \
           gui\screen\dl1_diagnostic_setup_screen.cpp \
           gui\screen\dl1_setup_screen.cpp \
           gui\screen\dl1_communication_setup_screen.cpp \
           gui\screen\dl1_aux_setup_screen.cpp \
           gui\screen\system_setup_screen.cpp \
           gui\screen\cu_setup_screen.cpp \


HEADERS  += gui\widget\runtime_widget_es.h \
            gui\widget\information_widget.h \
            gui\widget\brightness_widget.h \
            gui\widget\navigation_widget.h \
            gui\widget\background_widget.h \
            gui\widget\button.h \
            gui\widget\display_alive_widget.h \
            gui\base_screen.h \
            gui\widget\title_widget.h \
            gui\widget\scalable_widget.h \
            gui\runtime_screen.h \
            gui\navigation_controller.h \
            gui\widget\runtime_widget_a.h \
            gui\widget\runtime_widget_b.h \
            gui\widget\runtime_widget_c.h \
            gui\widget\runtime_widget_d.h \
            gui\widget\runtime_widget_e.h \
            gui\widget\runtime_widget_dl1.h \
            gui\widget_enum.h \
            gui\widget\runtime_widget.h \
            gui\widget\transparent_info_button.h \
            gui\widget\system_widget.h \
            gui\widget\system_widget_container.h \
            gui\widget\dl1_runtime_widget_b.h \
            gui\widget\es_runtime_widget_b.h \
            gui\widget\boat_button.h \
            gui\widget\item_widget.h \
            gui\widget\selectable_item_widget.h \
            gui\widget\item_widget_container.h \
            gui\widget\selectable_item_widget_container.h \
            gui\widget\selectable_enum_item_widget.h \
            gui\widget\selectable_int_item_widget.h \
            gui\widget\selectable_float_item_widget.h \
            gui\widget\selectable_string_item_widget.h \
            gui\widget\selectable_ip_item_widget.h \
            gui\widget\selectable_bool_item_widget.h \
            gui\widget\validator.h \
            gui\screen\base_screen.h \
            gui\widget\arrow_widget.h \
            gui\widget\horizontal_item_widget.h \
            gui\widget\horizontal_item_widget_container.h \
            gui\widget\up_down_widget.h \
            gui\widget\leg_button.h \
            gui\widget\calibration_graph_widget.h \
            gui\screen\runtime_screen.h \
            gui\screen\setup_menu_screen.h \
            gui\screen\boat_menu_screen.h \
            gui\screen\es_runtime_screen.h \
            gui\screen\setup_screen.h \
            gui\screen\multi_setup_screen.h \
            gui\screen\base_runtime_setup_screen.h \
            gui\screen\dl2_runtime_a_setup_screen.h \
            gui\screen\dl2_runtime_b_setup_screen.h \
            gui\screen\dl2_runtime_c_setup_screen.h \
            gui\screen\dl2_runtime_d_setup_screen.h \
            gui\screen\dl2_runtime_e_setup_screen.h \
            gui\screen\dl2_runtime_setup_screen.h \
            gui\screen\dl2_calibration_status_setup_screen.h \
            gui\screen\dl2_calibration_inst_angle_setup_screen.h \
            gui\screen\dl2_calibration_speed_setup_screen.h \
            gui\screen\dl2_calibration_speed_manual_gps_setup_screen.h \
            gui\screen\dl2_calibration_speed_manual_setup_screen.h \
            gui\screen\dl2_calibration_speed_sea_setup_screen.h \
            gui\screen\dl2_calibration_speed_auto_setup_screen.h \
            gui\screen\dl2_calibration_tilt_setup_screen.h \
            gui\screen\dl2_calibration_temp_setup_screen.h \
            gui\screen\dl2_calibration_setup_screen.h \
            gui\screen\dl2_alert_setup_screen.h \
            gui\screen\dl2_diagnostic_setup_screen.h \
            gui\screen\dl2_setup_screen.h \
            gui\screen\dl2_setup_setup_screen.h \
            gui\screen\dl2_setup_options_screen.h \
            gui\screen\dl2_communication_setup_screen.h \
            gui\screen\dl2_aux_setup_screen.h \
            gui\screen\dl2_jb70_setup_screen.h \
            gui\screen\es_runtime_a_setup_screen.h \
            gui\screen\es_runtime_b_setup_screen.h \
            gui\screen\es_runtime_setup_screen.h \
            gui\screen\es_alert_setup_screen.h \
            gui\screen\es_diagnostic_setup_screen.h \
            gui\screen\es_setup_screen.h \
            gui\screen\es_communication_setup_screen.h \
            gui\screen\es_aux_setup_screen.h \
            gui\screen\es_history_setup_screen.h \
            gui\screen\es_jb70_setup_screen.h \
            gui\screen\dl1_runtime_a_setup_screen.h \
            gui\screen\dl1_runtime_b_setup_screen.h \
            gui\screen\dl1_runtime_setup_screen.h \
            gui\screen\dl1_calibration_setup_screen.h \
            gui\screen\dl1_alert_setup_screen.h \
            gui\screen\dl1_diagnostic_setup_screen.h \
            gui\screen\dl1_setup_screen.h \
            gui\screen\dl1_communication_setup_screen.h \
            gui\screen\dl1_aux_setup_screen.h \
            gui\screen\system_setup_screen.h \
            gui\screen\cu_setup_screen.h
