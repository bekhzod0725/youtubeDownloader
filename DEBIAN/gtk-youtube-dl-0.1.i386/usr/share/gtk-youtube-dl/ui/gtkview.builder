<?xml version="1.0" encoding="UTF-8"?>
<interface>
  <requires lib="gtk+" version="2.24"/>
  <!-- interface-naming-policy project-wide -->
  <object class="GtkAction" id="action1"/>
  <object class="GtkFileChooserDialog" id="dlgFile">
    <property name="can_focus">False</property>
    <property name="border_width">5</property>
    <property name="title" translatable="yes">Choose destination file:</property>
    <property name="destroy_with_parent">True</property>
    <property name="type_hint">dialog</property>
    <property name="transient_for">wMain</property>
    <property name="action">save</property>
    <child internal-child="vbox">
      <object class="GtkVBox" id="dialog-vbox1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="spacing">2</property>
        <child internal-child="action_area">
          <object class="GtkHButtonBox" id="dialog-action_area1">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="layout_style">end</property>
            <child>
              <object class="GtkButton" id="btnCancel">
                <property name="label">gtk-cancel</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_action_appearance">False</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="btnSav">
                <property name="label">gtk-save</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
                <property name="use_action_appearance">False</property>
                <property name="use_stock">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="pack_type">end</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <placeholder/>
        </child>
      </object>
    </child>
    <action-widgets>
      <action-widget response="0">btnCancel</action-widget>
      <action-widget response="1">btnSav</action-widget>
    </action-widgets>
  </object>
  <object class="GtkWindow" id="wMain">
    <property name="width_request">530</property>
    <property name="height_request">250</property>
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">GTK2 Youtube Downloader</property>
    <property name="resizable">False</property>
    <signal name="destroy" handler="on_wMain_destroy" swapped="no"/>
    <child>
      <object class="GtkLayout" id="layout1">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <child>
          <object class="GtkEntry" id="txtUrl">
            <property name="width_request">320</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="invisible_char">•</property>
            <property name="primary_icon_activatable">False</property>
            <property name="secondary_icon_activatable">False</property>
            <property name="primary_icon_sensitive">True</property>
            <property name="secondary_icon_sensitive">True</property>
          </object>
          <packing>
            <property name="x">100</property>
            <property name="y">20</property>
          </packing>
        </child>
        <child>
          <object class="GtkLabel" id="lblUrl">
            <property name="width_request">100</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="label" translatable="yes">Enter URL:</property>
          </object>
          <packing>
            <property name="x">9</property>
            <property name="y">20</property>
          </packing>
        </child>
        <child>
          <object class="GtkButton" id="btnSearch">
            <property name="label" translatable="yes">Search</property>
            <property name="width_request">80</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="receives_default">True</property>
            <property name="use_action_appearance">False</property>
            <signal name="clicked" handler="on_btnSearch_clicked" swapped="no"/>
          </object>
          <packing>
            <property name="x">433</property>
            <property name="y">20</property>
          </packing>
        </child>
        <child>
          <object class="GtkComboBox" id="qualBox">
            <property name="width_request">320</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <signal name="changed" handler="on_qualBox_changed" swapped="no"/>
          </object>
          <packing>
            <property name="x">100</property>
            <property name="y">70</property>
          </packing>
        </child>
        <child>
          <object class="GtkEntry" id="txtOut">
            <property name="width_request">320</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="invisible_char">•</property>
            <property name="primary_icon_activatable">False</property>
            <property name="secondary_icon_activatable">False</property>
            <property name="primary_icon_sensitive">True</property>
            <property name="secondary_icon_sensitive">True</property>
          </object>
          <packing>
            <property name="x">100</property>
            <property name="y">100</property>
          </packing>
        </child>
        <child>
          <object class="GtkLabel" id="lblQual">
            <property name="width_request">100</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="label" translatable="yes">Quality:</property>
          </object>
          <packing>
            <property name="x">9</property>
            <property name="y">70</property>
          </packing>
        </child>
        <child>
          <object class="GtkLabel" id="lblOut">
            <property name="width_request">100</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="label" translatable="yes">Output file:</property>
          </object>
          <packing>
            <property name="x">9</property>
            <property name="y">100</property>
          </packing>
        </child>
        <child>
          <object class="GtkButton" id="btnChoose">
            <property name="label" translatable="yes">Choose</property>
            <property name="width_request">80</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="receives_default">True</property>
            <property name="use_action_appearance">False</property>
            <signal name="clicked" handler="on_btnChoose_clicked" swapped="no"/>
          </object>
          <packing>
            <property name="x">433</property>
            <property name="y">100</property>
          </packing>
        </child>
        <child>
          <object class="GtkButton" id="btnSave">
            <property name="label" translatable="yes">Save</property>
            <property name="width_request">80</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="receives_default">True</property>
            <property name="use_action_appearance">False</property>
            <signal name="clicked" handler="on_btnSave_clicked" swapped="no"/>
          </object>
          <packing>
            <property name="x">383</property>
            <property name="y">150</property>
          </packing>
        </child>
        <child>
          <object class="GtkButton" id="btnExit">
            <property name="label" translatable="yes">Exit
</property>
            <property name="width_request">80</property>
            <property name="height_request">20</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="receives_default">True</property>
            <property name="use_action_appearance">False</property>
            <signal name="clicked" handler="on_btnExit_clicked" swapped="no"/>
          </object>
          <packing>
            <property name="x">65</property>
            <property name="y">150</property>
          </packing>
        </child>
        <child>
          <object class="GtkTextView" id="txtResults">
            <property name="width_request">530</property>
            <property name="height_request">70</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="editable">False</property>
          </object>
          <packing>
            <property name="y">180</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
