/*
 * ManageApplicationsJPanel.java
 *
 * Created on 23. Februar 2005, 09:04
 */

package org.dyndns.widerstand.openplatformmanager;

import java.util.Arrays;
import org.dyndns.widerstand.OpenPlatform.OPSPApplet;

/**
 *
 * @author  Widerstand
 */
public class ManageApplicationsJPanel extends javax.swing.JPanel {
    
    private MainJFrame parent;
    private javax.swing.JPanel jPanelStatus;
    
    /** Creates new form ManageApplicationsJPanel */
    public ManageApplicationsJPanel(MainJFrame parent) {
        this.parent = parent;
        initComponents();
    }
    
    private void initConditionalComponents() {
        jTabbedPane1.remove(jPanelStatus);
        jPanelStatus = new StatusJPanel(parent);
        jTabbedPane1.addTab("Status", jPanelStatus);
    }
    
    private void removeConditionalComponents() {
        jTabbedPane1.remove(jPanelStatus);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        jTabbedPane1 = new javax.swing.JTabbedPane();
        jPanelDelete = new DeleteJPanel(parent);
        jPanelInstall = new InstallJPanel(parent);

        setLayout(new java.awt.BorderLayout());

        setBorder(new javax.swing.border.CompoundBorder(new javax.swing.border.TitledBorder("Manage Applications"), new javax.swing.border.EmptyBorder(new java.awt.Insets(5, 5, 5, 5))));
        jTabbedPane1.addTab("Delete", jPanelDelete);

        jTabbedPane1.addTab("Install", jPanelInstall);

        add(jTabbedPane1, java.awt.BorderLayout.CENTER);

    }//GEN-END:initComponents
    
    public void refresh() {
        if (Arrays.equals(parent.session.selectedApplication, OPSPApplet.OPSP_CARD_MANAGER_AID)) {
            initConditionalComponents();
            ((StatusJPanel)jPanelStatus).refresh();
        }

        else {
            removeConditionalComponents();
        }
        ((InstallJPanel)jPanelInstall).refresh();
        ((DeleteJPanel)jPanelDelete).refresh();
    }
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JPanel jPanelDelete;
    private javax.swing.JPanel jPanelInstall;
    private javax.swing.JTabbedPane jTabbedPane1;
    // End of variables declaration//GEN-END:variables
    
}
