//
//  KinectModel.cpp
//  urModernDriverTest
//
//  Created by dantheman on 2/20/16.
// Copyright (c) 2016, Daniel Moore, Madaline Gannon, and The Frank-Ratchye STUDIO for Creative Inquiry All rights reserved.
//

#include "RobotModel.h"
using namespace ofxRobotArm;
RobotModel::RobotModel(){
    pose = vector<ofxRobotArm::Pose>();
}
RobotModel::~RobotModel(){
    
}

// D-H Parameters for UR Robot Arms:
// https://www.universal-robots.com/articles/ur/parameters-for-calculations-of-kinematics-and-dynamics/
void RobotModel::setup(RobotType type){
    this->type = type;
    pose.resize(6);
    nodes.resize(6);
    vector<Pose> foopose;
    foopose.resize(6);
    
    if(type == RobotType::UR3 || type == RobotType::UR5 || type == RobotType::UR10){
        if(type == RobotType::UR3){
            ofLog(OF_LOG_NOTICE)<<"LOADING ROBOTYPE UR3"<<endl;
            if(loader.loadModel(ofToDataPath("models/ur3.dae"))){
                for(int i = 0; i < loader.getNumMeshes(); i++){
                    meshs.push_back(loader.getMesh(i));
                }
            }else{
                ofLogFatalError()<<"PLEASE PLACE THE 3D FILES OF THE UR ARM IN data/models/ur3.dae"<<endl;
            }
            
            pose[0].position.set(0, 0, 0);
            pose[1].position.set(0, 0, 0);
            pose[2].position.set(0, 0, 0);
            pose[3].position.set(0, 0, 0);
            pose[4].position.set(0, 0, 0);
            pose[5].position.set(0, 0, 0);
            
        }else if (type == RobotType::UR5){
            ofLog(OF_LOG_NOTICE)<<"LOADING ROBOTYPE UR5"<<endl;
            if(loader.loadModel(ofToDataPath("models/ur5.dae"))){
                for(int i = 0; i < loader.getNumMeshes(); i++){
                    meshs.push_back(loader.getMesh(i));
                }
            }else{
                ofLogFatalError()<<"PLEASE PLACE THE 3D FILES OF THE UR ARM IN data/models/ur5.dae"<<endl;
            }
            
            pose[0].position.set(0, 0, 0);
            pose[1].position.set(0, -0.072238, 0.083204);
            pose[2].position.set(0, -0.077537, 0.51141);
            pose[3].position.set(0, -0.070608, 0.903192);
            pose[4].position.set(0, -0.117242, 0.950973);
            pose[5].position.set(0, -0.164751, 0.996802);
            
        }  else if (type == RobotType::UR10){
            ofLog(OF_LOG_NOTICE)<<"LOADING ROBOTYPE UR10"<<endl;
            // should load model from addon data path, not app
            if(loader.loadModel(ofToDataPath("models/ur10.dae"))){
                for(int i = 0; i < loader.getNumMeshes(); i++){
                    meshs.push_back(loader.getMesh(i));
                }
            }else{
                ofLogFatalError()<<"PLEASE PLACE THE 3D FILES OF THE UR ARM IN data/models/ur10.dae"<<endl;
            }
            
            pose[0].position.set(0, 0, 0);
            
            // These are correct joint positions for the non-home D-H position.
            // Reference: https://asd.sutd.edu.sg/dfab/a-geometric-inverse-kinematics-solution-for-the-universal-robot/
            // These are correct joint positions for the HOME position (0 rotations on each joint).
            pose[1].position.set(0, -.086, .1273);
            pose[2].position.set(0, -.1163, .7393);
            pose[3].position.set(0, -.1094, 1.3116);
            pose[4].position.set(0, -0.16395, 1.3733);
            pose[5].position.set(0, -0.22535, 1.4273);
            
        }
        
        // Setup the joint axes
        pose[0].axis.set(0, 0, 1);
        pose[1].axis.set(0, -1, 0);
        pose[2].axis.set(0, -1, 0);
        pose[3].axis.set(0, -1, 0);
        pose[4].axis.set(0, 0, 1);
        pose[5].axis.set(0, 1, 0);
        
        tool.axis.set(pose[5].axis);
        
        pose[0].orientation.makeRotate(0,pose[0].axis);
        pose[1].orientation.makeRotate(-90,pose[1].axis);
        pose[2].orientation.makeRotate(0,pose[2].axis);
        pose[3].orientation.makeRotate(-90,pose[3].axis);
        pose[4].orientation.makeRotate(0,pose[4].axis);
        pose[5].orientation.makeRotate(0,pose[5].axis);
    }
    
    if(type == RobotType::IRB120){
        ofLog(OF_LOG_NOTICE)<<"LOADING ROBOTYPE IRB120"<<endl;
        if(loader.loadModel(ofToDataPath("models/irb120.dae"))){
            for(int i = 0; i < loader.getNumMeshes(); i++){
                meshs.push_back(loader.getMesh(i));
            }
        }else{
            ofLogFatalError()<<"PLEASE PLACE THE 3D FILES OF THE UR ARM IN data/models/irb120.dae"<<endl;
        }
        // Reference: https://library.e.abb.com/public/7139d7f4f2cb4d0da9b7fac6541e91d1/3HAC035960%20PS%20IRB%20120-en.pdf
        // ROS https://github.com/ros-industrial/abb_experimental/blob/kinetic-devel/abb_irb120_support/urdf/irb120_3_58_macro.xacro
        
        pose[0].position.set(0, 0, 0);
        pose[1].position.set(0, 0, 0.270);
        pose[2].position.set(0, 0, 0.560);
        pose[3].position.set(0.134,0, 0.630);
        pose[4].position.set(0.302,0, 0.630);
        pose[5].position.set(0.374,0, 0.630);
        
        pose[0].axis.set(0, 0, 1);
        pose[1].axis.set(0, 1, 0);
        pose[2].axis.set(0, 1, 0);
        pose[3].axis.set(-1, 0, 0);
        pose[4].axis.set(0, 1, 0);
        pose[5].axis.set(1, 0, 0);
        
        pose[0].orientation.makeRotate(0,pose[0].axis);
        pose[1].orientation.makeRotate(0,pose[1].axis);
        pose[2].orientation.makeRotate(90,pose[2].axis);
        pose[3].orientation.makeRotate(0,pose[3].axis);
        pose[4].orientation.makeRotate(0,pose[4].axis);
        pose[5].orientation.makeRotate(0,pose[5].axis);
        
        pose[0].rotation = 0;
        pose[1].rotation = 0;
        pose[2].rotation = 0;
        pose[3].rotation = 0;
        pose[4].rotation = 0;
        pose[5].rotation = 0;
    }
    
    
    tool.position.set(pose[5].position + ofVec3f(0,-0.0308,0)); // flange position
    
    for(int i = 1; i <pose.size(); i++){
        pose[i].offset =pose[i].position-pose[i-1].position;
        ofLog(OF_LOG_NOTICE)<<"JOINT: "<<i<<" OFFSETS XYZ"<<pose[i].offset<<endl;
    }
    tool.offset = pose[5].offset;
    
    
    // Rig Joints
    nodes[0].setPosition(pose[0].position);
    nodes[0].setOrientation(pose[0].orientation);
    for(int i = 1; i <nodes.size(); i++){
        nodes[i].setParent(nodes[i-1]);
        nodes[i].setPosition(pose[i].offset*1000);
        nodes[i].setOrientation(pose[i].orientation);
    }
    
    
    // Set Tool Center Point Node
    tcpNode.setParent(nodes[5]);
    tcpNode.setPosition(ofVec3f(0.0, -0.0308, 0.0)*1000);
    
    // Set Tool Rotations
    tool.rotation =pose[5].rotation;
    
    shader.load("shaders/model");
    
    bDrawModel.set("Draw Model", true);
    bDrawTargetModel.set("Draw Target Model", true);
    bUseShader.set("Use Shader", true);
}

ofQuaternion RobotModel::getToolPointQuaternion(){
    return toOf(nodes[5].getGlobalTransformMatrix()).getRotate();
}


ofNode RobotModel::getTool(){
    return tcpNode;
}

void RobotModel::setToolOffset(ofVec3f localOffset){
    tcpNode.setPosition(localOffset);
}

void RobotModel::setAngles( vector<double> aTargetRadians ){
    if(type == RobotType::UR5 || type == RobotType::UR3 || type == RobotType::UR10){
        for(int i = 0; i < pose.size(); i++){
            if(i == 1 || i == 3){
                pose[i].orientation.makeRotate(ofRadToDeg(aTargetRadians[i])+90,pose[i].axis);
            }else{
                pose[i].orientation.makeRotate(ofRadToDeg(aTargetRadians[i]),pose[i].axis);
            }
            nodes[i].setOrientation(pose[i].orientation);
        }
    }else{
        for(int i = 0; i < pose.size(); i++){
            pose[i].orientation.makeRotate(ofRadToDeg(aTargetRadians[i]),pose[i].axis);
            pose[i].rotation = ofRadToDeg(aTargetRadians[1]);
            ofLog()<<"axis "<<pose[i].axis<<" angle"<<pose[i].rotation<<endl;
            nodes[i].setOrientation(pose[i].orientation);
        }
    }
}

void RobotModel::setPose(vector<double> pose){
    if(type == RobotType::UR5 || type == RobotType::UR3 || type == RobotType::UR10){
        for(int i = 0; i < pose.size(); i++){
            if(i == 1 || i == 3){
                this->pose[i].orientation.makeRotate(ofRadToDeg(pose[i])+90,this->pose[i].axis);
                this->pose[i].rotation = ofRadToDeg(pose[i])+90;
            }else{
                this->pose[i].orientation.makeRotate(ofRadToDeg(pose[i]),this->pose[i].axis);
                this->pose[i].rotation = ofRadToDeg(pose[i]);
            }
            nodes[i].setOrientation(this->pose[i].orientation);
        }
    }else{
        for(int i = 0; i < pose.size(); i++){
            this->pose[i].rotation = (ofRadToDeg(pose[i]));
            ofLog()<<this->pose[i].axis<<endl;
            this->pose[i].orientation.makeRotate(this->pose[i].rotation,this->pose[i].axis);
            nodes[i].setOrientation(this->pose[i].orientation);
        }
    }
}

void RobotModel::setEndEffector(string filename){
    string path = ofToDataPath("models/"+filename);
    
    loader.clear();
    if (loader.loadModel("models/"+filename))
    {
        toolMesh = loader.getMesh(0);
    }
    else{
        ofLogFatalError()<<"PLEASE PLACE THE 3D FILES OF THE END EFFECTOR IN data/models/" << filename <<endl;
    }
}

void RobotModel::clearEndEffector(){
    toolMesh.clear();
}

void RobotModel::setToolMesh(ofMesh mesh){
    toolMesh = mesh;
}
void RobotModel::update(){
    
}

// ----------------------------------------------------------
void RobotModel::drawSkeleton() {
    ofEnableDepthTest();
    {
        ofPushStyle();
        {
            int i = 0;
            float dist = 0;
            for (auto joint : nodes) {
                
                // draw each joint
                if (i != 0) {
                    joint.draw();
                }
                ofVec3f p = joint.getGlobalPosition();
                
                // draw each link
                ofPushStyle();
                float t = i / float(nodes.size());
                ofColor mag = ofColor(255, 0, 255);
                ofColor yellow = ofColor(255, 255, 0);
                ofSetColor(mag.getLerped(yellow, t));
                ofSetLineWidth(5);
                
                if (i != 0) {
                    ofDrawLine(nodes[i - 1].getGlobalPosition(), p);
                    dist = p.distance(nodes[i - 1].getGlobalPosition());
                }
                ofPopStyle();
                
                // show length of each link
                ofSetColor(60, 80);
                if (i == 0)
                    ofDrawBitmapString(dist, p.getInterpolated(ofVec3f(), .5));
                else
                    ofDrawBitmapString(dist, p.getInterpolated(nodes[i - 1].getGlobalPosition(), .5));
                
                // show joint id
                ofSetColor(60, 90);
                ofDrawBitmapString(ofToString(i), p.x + 5, p.y, p.z + 5);
                
                // show angle at joint
                ofDrawBitmapString("angle: " + ofToString(pose[i].rotation), p.x + 5, p.y, p.z - 20);
                
                i++;
            }
        }
        ofPopStyle();
    }
    ofEnableDepthTest();
}


void RobotModel::draw(ofFloatColor color, bool bDrawDebug){
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor(255, 255, 255);
    if(bDrawDebug) {
        ofPushStyle(); {
            ofDrawAxis(1000);
            ofSetColor(255, 255, 0);
            ofDrawSphere(tool.position*ofVec3f(1000, 1000, 1000), 40);
            ofSetColor(225, 225, 225);
        } ofPopStyle();
    }
    
//        if(bDrawModel){
//            ofEnableDepthTest();
//            ofQuaternion q;
//            ofVec3f offset;
//    
//            ofMatrix4x4 gmat;
//            gmat.makeIdentityMatrix();
//            gmat.makeScaleMatrix( 1, 1, 1 );
//    
//            if(bUseShader){
//    
//                shader.begin();
//                shader.setUniform4f("color", color);
//            }
//                    ofPushMatrix();
//                    {
//                        ofPushMatrix();
//                        {
//                            int i = 0;
//                            for(auto &joint : pose)//pose.size(); i++)
//                            {
//                                float x;
//                                ofVec3f axis;
//                                q = joint.orientation;
//                                q.getRotate(x, axis);
//                                ofTranslate(pose[i].offset*1000);
//                                gmat.translate( pose[i].offset*1000 );
//    
//                                if(bDrawDebug) {
//                                    ofDrawAxis(30);
//                                }
//                                ofMatrix4x4 tmat;
//                                if(i >= 3){
//                                    ofPushMatrix();
//                                    {
//                                        ofRotateDeg(90, 0, 0, 1);
//                                        ofRotateDeg(90, 1, 0, 0);
//                                        ofScale(100, 100, 100);
//                                        meshs[i].draw();
//                                    }
//                                    ofPopMatrix();
//                                }
//                                ofRotateDeg(x, axis.x, axis.y, axis.z);
//                                if(i < 3){
//                                    ofPushMatrix();
//                                    {
//                                        ofRotateDeg(90, 0, 0, 1);
//                                        ofRotateDeg(90, 1, 0, 0);
//                                        ofScale(100, 100, 100);
//    
//                                        meshs[i].draw();
//                                    } ofPopMatrix();
//                                }
//                                if (i==5){
//                                    // include flange offset
//                                    ofTranslate(0, -0.0308 * 1000, 0);
//                                    // the x-axis was rotating backwards,
//                                    // so I'm doing some funny business here
//            //                        ofRotateDeg(180, 0, 0, 1);
//                                    ofRotateDeg(-180, nodes[5].getXAxis().x,
//                                                nodes[5].getXAxis().y,
//                                                nodes[5].getXAxis().z);
//                                    toolMesh.drawWireframe();
//                                }
//                                i++;
//                            }
//                        }
//                        ofPopMatrix();
//                    }
//                    ofPopMatrix();
//            ofDisableDepthTest();
//    
//            if(bUseShader) shader.end();
//        }
//    
    
    ofPushMatrix();
    {
        drawSkeleton();
    }
    ofPopMatrix();
    
    
    
    
    ofPopStyle();
    ofPopMatrix();
}