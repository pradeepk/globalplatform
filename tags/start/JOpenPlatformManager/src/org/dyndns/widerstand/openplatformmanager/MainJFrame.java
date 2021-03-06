/*
 * MainJFrame.java
 *
 * Created on 18. Februar 2005, 03:17
 */

package org.dyndns.widerstand.openplatformmanager;

import java.awt.Component;
import java.util.*;
import javax.swing.*;
import java.awt.event.ActionEvent;

import org.dyndns.widerstand.OpenPlatform.*;

/**
 *
 * @author  Widerstand
 */
public class MainJFrame extends javax.swing.JFrame {
    
    public SessionInformation session;
    
    /** Creates new form MainJFrame */
    public MainJFrame() {
        initComponents();
        disableAfterDisconnect();
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        jPanel1 = new javax.swing.JPanel();
        jTabbedPane1 = new javax.swing.JTabbedPane();
        jPanelConnectionManagement = new ConnectionManagementJPanel(this);
        jPanelManageApplications = new ManageApplicationsJPanel(this);
        jPanelKeyManagement = new KeyManagementJPanel(this);
        jPanelDAPManagement = new DAPManagementJPanel(this);

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        addWindowListener(new java.awt.event.WindowAdapter() {
            public void windowClosed(java.awt.event.WindowEvent evt) {
                formWindowClosed(evt);
            }
        });

        jPanel1.setLayout(new java.awt.BorderLayout());

        jPanel1.setMinimumSize(new java.awt.Dimension(1024, 768));
        jPanel1.setPreferredSize(new java.awt.Dimension(1024, 768));
        jPanel1.setRequestFocusEnabled(false);
        jTabbedPane1.addTab("Manage Connection", jPanelConnectionManagement);

        jTabbedPane1.addTab("Manage Applications", jPanelManageApplications);

        jTabbedPane1.addTab("Manage Keys", jPanelKeyManagement);

        jTabbedPane1.addTab("Manage DAPs", jPanelDAPManagement);

        jPanel1.add(jTabbedPane1, java.awt.BorderLayout.CENTER);

        getContentPane().add(jPanel1, java.awt.BorderLayout.CENTER);

        pack();
    }//GEN-END:initComponents
    
    private void formWindowClosed(java.awt.event.WindowEvent evt) {//GEN-FIRST:event_formWindowClosed
        try {
            if (session.cardHandle != 0) {
                OPSPWrapper.cardDisconnect(session.cardHandle);
            }
            if (session.cardContext != 0) {
                OPSPWrapper.releaseContext(session.cardContext);
            }
        } catch (OPSPException e) {
            javax.swing.JOptionPane.showMessageDialog(this, e.getMessage(),
                    "Open Platform Error", javax.swing.JOptionPane.ERROR_MESSAGE);
            return;
        }
    }//GEN-LAST:event_formWindowClosed
        
    private int getComponentIndex(String id) {
        for (int i=0; i<jTabbedPane1.getTabCount(); i++) {
            if (jTabbedPane1.getTitleAt(i).equals(id)) {
                return i;
            }
        }
        return -1;
    }
        
    public void enableAfterConnect() {
        ((ConnectionManagementJPanel)jPanelConnectionManagement).enableAfterConnect();
        jTabbedPane1.setEnabledAt(getComponentIndex("Manage Applications"), true);
        jTabbedPane1.setEnabledAt(getComponentIndex("Manage Keys"), true);
        jTabbedPane1.setEnabledAt(getComponentIndex("Manage DAPs"), true);
        //        jMenuItem1.setEnabled(false);
        //        jMenuItem2.setEnabled(true);
        //        int k = getComponentIndex("Manage Applications");
        //        jTabbedPane1.setSelectedIndex(k);
        refreshStatus();
    }
    
    public void disableAfterDisconnect() {
        ((ConnectionManagementJPanel)jPanelConnectionManagement).disableAfterDisconnect();
        jTabbedPane1.setEnabledAt(getComponentIndex("Manage Applications"), false);
        jTabbedPane1.setEnabledAt(getComponentIndex("Manage Keys"), false);
        jTabbedPane1.setEnabledAt(getComponentIndex("Manage DAPs"), false);
        //        jMenuItem2.setEnabled(false);
        //        jMenuItem1.setEnabled(true);
    }
    
    public void enableAfterEstablishContext() {
        ((ConnectionManagementJPanel)jPanelConnectionManagement).enableAfterEstablishContext();
    }
    
    public void disableAfterReleaseContext() {
        disableAfterDisconnect();
        ((ConnectionManagementJPanel)jPanelConnectionManagement).disableAfterReleaseContext();
    }
    
    public void refreshStatus() {
        ((ManageApplicationsJPanel)jPanelManageApplications).refresh();
        ((DAPManagementJPanel)jPanelDAPManagement).refresh();
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainJFrame().setVisible(true);
            }
        });
    }
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanelConnectionManagement;
    private javax.swing.JPanel jPanelDAPManagement;
    private javax.swing.JPanel jPanelKeyManagement;
    private javax.swing.JPanel jPanelManageApplications;
    private javax.swing.JTabbedPane jTabbedPane1;
    // End of variables declaration//GEN-END:variables
    
}
