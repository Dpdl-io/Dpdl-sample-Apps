/**
 *                   Dpdl3DMolecule
 

This java class is used within the Dpdl sample application 'Dpdl3DMolecule', loaded and executed as java object in 'dpdl3DJavaFX_molecule.h' 

https://github.com/Dpdl-io/Dpdl-sample-Apps/blob/main/Dpdl3DMolecules.md
 
The code below has been adopted from the JavaFX examples at: https://docs.oracle.com/javase/8/javafx/graphics-tutorial/sampleapp3d.htm#CJAHFAF                              
 */
package dpdl.dpdlLibs.javafx.test;

import javafx.scene.Group;
import javafx.scene.transform.Rotate;
import javafx.scene.transform.Scale;
import javafx.scene.transform.Translate;
import javafx.scene.Node;

public class DpdlTestForm extends Group {

    public enum RotateOrder {
        XYZ, XZY, YXZ, YZX, ZXY, ZYX
    }

    public Translate t  = new Translate(); 
    public Translate p  = new Translate(); 
    public Translate ip = new Translate(); 
    public Rotate rx = new Rotate();
    { rx.setAxis(Rotate.X_AXIS); }
    public Rotate ry = new Rotate();
    { ry.setAxis(Rotate.Y_AXIS); }
    public Rotate rz = new Rotate();
    { rz.setAxis(Rotate.Z_AXIS); }
    public Scale s = new Scale();

    public DpdlTestForm() { 
        super(); 
        getTransforms().addAll(t, rz, ry, rx, s); 
    }

    public DpdlTestForm(RotateOrder rotateOrder) { 
        super(); 
        // choose the order of rotations based on the rotateOrder
        switch (rotateOrder) {
        case XYZ:
            getTransforms().addAll(t, p, rz, ry, rx, s, ip); 
            break;
        case XZY:
            getTransforms().addAll(t, p, ry, rz, rx, s, ip); 
            break;
        case YXZ:
            getTransforms().addAll(t, p, rz, rx, ry, s, ip); 
            break;
        case YZX:
            getTransforms().addAll(t, p, rx, rz, ry, s, ip);
            break;
        case ZXY:
            getTransforms().addAll(t, p, ry, rx, rz, s, ip); 
            break;
        case ZYX:
            getTransforms().addAll(t, p, rx, ry, rz, s, ip); 
            break;
        }
    }
    
    public void setAngleRotRY(double angle) {
    	ry.setAngle(angle);
    }
    
    public void setAngleRotRX(double angle) {
    	rx.setAngle(angle);
    	
    }
    
    public void addAllTMP3(Node n1, Node n2, Node n3) {
    	this.getChildren().addAll(n1, n2, n3);
    }
    
    public void addAllTMP1(Node n1) {
    	this.getChildren().addAll(n1);
    }
    
    public void addAllChild(Node... nodes) {
    	this.getChildren().addAll(nodes);
    }
    
    public void testVA(String... args) {
    	System.out.println("testVA()");
    }

    public void setTranslate(double x, double y, double z) {
        t.setX(x);
        t.setY(y);
        t.setZ(z);
    }

    public void setTranslate(double x, double y) {
        t.setX(x);
        t.setY(y);
    }

    public void setTx(double x) { t.setX(x); }
    public void setTy(double y) { t.setY(y); }
    public void setTz(double z) { t.setZ(z); }

    public void setRotate(double x, double y, double z) {
        rx.setAngle(x);
        ry.setAngle(y);
        rz.setAngle(z);
    }

    public void setRotateX(double x) { rx.setAngle(x); }
    public void setRotateY(double y) { ry.setAngle(y); }
    public void setRotateZ(double z) { rz.setAngle(z); }
    public void setRx(double x) { rx.setAngle(x); }
    public void setRy(double y) { ry.setAngle(y); }
    public void setRz(double z) { rz.setAngle(z); }

    public void setScale(double scaleFactor) {
        s.setX(scaleFactor);
        s.setY(scaleFactor);
        s.setZ(scaleFactor);
    }

    public void setScale(double x, double y, double z) {
        s.setX(x);
        s.setY(y);
        s.setZ(z);
    }

    public void setSx(double x) { s.setX(x); }
    public void setSy(double y) { s.setY(y); }
    public void setSz(double z) { s.setZ(z); }

    public void setPivot(double x, double y, double z) {
        p.setX(x);
        p.setY(y);
        p.setZ(z);
        ip.setX(-x);
        ip.setY(-y);
        ip.setZ(-z);
    }

    public void reset() {
        t.setX(0.0);
        t.setY(0.0);
        t.setZ(0.0);
        rx.setAngle(0.0);
        ry.setAngle(0.0);
        rz.setAngle(0.0);
        s.setX(1.0);
        s.setY(1.0);
        s.setZ(1.0);
        p.setX(0.0);
        p.setY(0.0);
        p.setZ(0.0);
        ip.setX(0.0);
        ip.setY(0.0);
        ip.setZ(0.0);
    }

    public void resetTSP() {
        t.setX(0.0);
        t.setY(0.0);
        t.setZ(0.0);
        s.setX(1.0);
        s.setY(1.0);
        s.setZ(1.0);
        p.setX(0.0);
        p.setY(0.0);
        p.setZ(0.0);
        ip.setX(0.0);
        ip.setY(0.0);
        ip.setZ(0.0);
    }

    @Override public String toString() {
        return "DpdlTestForm[t = (" +
                           t.getX() + ", " +
                           t.getY() + ", " +
                           t.getZ() + ")  " +
                           "r = (" +
                           rx.getAngle() + ", " +
                           ry.getAngle() + ", " +
                           rz.getAngle() + ")  " +
                           "s = (" +
                           s.getX() + ", " + 
                           s.getY() + ", " + 
                           s.getZ() + ")  " +
                           "p = (" +
                           p.getX() + ", " + 
                           p.getY() + ", " + 
                           p.getZ() + ")  " +
                           "ip = (" +
                           ip.getX() + ", " + 
                           ip.getY() + ", " + 
                           ip.getZ() + ")]";
    }
}

