/*
 * ProgressJDialog.java
 *
 * Created on 6. Mai 2005, 00:00
 */

package org.dyndns.widerstand.openplatformmanager;

import java.awt.Rectangle;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import javax.swing.JDialog;


/**
 * Wait for a method to finish and displays a moving progress bar while operation is running.
 * @author Karsten Ohme
 */
public class WaitForMethodJDialog extends javax.swing.JDialog {
    
    private String className;
    private String methodName;
    private Object[] parameters;
    private Class[] parameterTypes;
    private Object obj;
    private SwingWorker swingWorker;
    private WaitForMethodJDialog dialog;
    
    /**
     * Creates new form WaitForMethodJDialog
     * @param parent The parent frame.
     * @param methodName The name of the method to call.
     * @param obj The object at which the method with <code>methodName</code> is called.
     * @param parameterTypes The corresponding <code>Class</code> array to the <code>parameters</code>
     * @param parameters The parameters given to the method with <code>methodName</code>.
     */
    private WaitForMethodJDialog(java.awt.Frame parent, String className,
            String methodName, Object obj, Class[] parameterTypes, Object[] parameters) {
        super(parent, true);
        this.className = className;
        this.methodName = methodName;
        this.parameters = parameters;
        this.parameterTypes = parameterTypes;
        this.obj = obj;
        initComponents();
    }
    
    /**
     * Creates new form WaitForMethodJDialog
     * @param parent The parent frame.
     * @param methodName The name of the method to call.
     * @param obj The object at which the method with <code>methodName</code> is called.
     * @param parameterTypes The corresponding <code>Class</code> array to the <code>parameters</code>
     * @param parameters The parameters given to the method with <code>methodName</code>.
     * @return The result of the given method.
     */
    public static Object showDialog(java.awt.Frame parent, String className,
            String methodName, Object obj, Class[] parameterTypes, Object[] parameters) throws Exception {
        WaitForMethodJDialog dialog = new WaitForMethodJDialog(parent, className, methodName, obj, 
                parameterTypes, parameters);
        dialog.dialog = dialog;
        dialog.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
        Rectangle rect = parent.getBounds();
        dialog.setLocation(rect.x + rect.width/2 - dialog.getWidth()/2, rect.y + rect.height/2 - dialog.getHeight()/2);
        dialog.createSwingWorker();
        dialog.setVisible(true);
        return dialog.getResult();
    }
    
    /**
     * Returns the result if the method given in the constructor.
     * You have to call this method, because if an exception occurs while
     * executing the method it is thrown here.
     * @return The result of the method given in the constructor.
     */
    private Object getResult() throws Exception {
        Object obj = swingWorker.get();
        if (obj == null)
            return null;
        if (obj instanceof Exception)
            throw (Exception)obj;
        return obj;
    }
    
    private void createSwingWorker() {
        swingWorker = new SwingWorker() {
            public Object construct() {
                try {
                    Class cls = Class.forName(className);
                    Method method = cls.getMethod(methodName, parameterTypes);
                    Object a= method.invoke(obj, parameters);
                    return a;
                } catch (InvocationTargetException e) {
                    return (Exception)e.getCause();
                } catch (Exception e) {
                    return e;
                }
            }
            public void finished() {
                dialog.setVisible(false);
            }
        };
        swingWorker.start();
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    private void initComponents() {//GEN-BEGIN:initComponents
        java.awt.GridBagConstraints gridBagConstraints;

        jPanel1 = new javax.swing.JPanel();
        jProgressBar1 = new javax.swing.JProgressBar();
        jLabelRunning = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        jPanel1.setLayout(new java.awt.GridBagLayout());

        jPanel1.setBorder(new javax.swing.border.CompoundBorder(new javax.swing.border.TitledBorder("Operation in Progress"), new javax.swing.border.EmptyBorder(new java.awt.Insets(5, 5, 5, 5))));
        jProgressBar1.setIndeterminate(true);
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel1.add(jProgressBar1, gridBagConstraints);

        jLabelRunning.setText(methodName+" is running ...");
        gridBagConstraints = new java.awt.GridBagConstraints();
        gridBagConstraints.insets = new java.awt.Insets(5, 5, 5, 5);
        jPanel1.add(jLabelRunning, gridBagConstraints);

        getContentPane().add(jPanel1, java.awt.BorderLayout.CENTER);

        pack();
    }//GEN-END:initComponents
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLabelRunning;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JProgressBar jProgressBar1;
    // End of variables declaration//GEN-END:variables
    
}
