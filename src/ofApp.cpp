#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//cam.setPosition(0, 0, 400);
	//cam.lookAt(ofVec3f(0, 0, 0));

	bvh.load("./kashiyuka.bvh");
	bvh.play();

	cout << bvh.getJoint(18) << endl;

	//bvh.getTpose();

	//IK計算用に情報を抜き出す
	for (int i = 0; i < bvh.getNumJoints(); i++)
	{
		IkJointsPosition[i] = bvh.getJoint(i)->getPosition();
	}

	for (int i = 0; i < bvh.getNumJoints()-1; i++)
	{
		IkJointsRotate[i] = bvh.getJoint(i+1)->getRotate();
	}


    /*
	joints[0].set(200, 200, 0);
	joints[1].set(400, 400, 0);
	joints[2].set(600, 200, 0);
	joints[3].set(800, 400, 0);
	target.set(1000, 2300, 0);*/

}

//--------------------------------------------------------------
void ofApp::update(){

	target.set(x, y, z);


	//末端から１つ目の関節
	ofVec3f VecTarget = (target - IkJointsPosition[16]).getNormalized();
	ofVec3f VecEffector = (IkJointsPosition[17] - IkJointsPosition[16]).getNormalized();

	ofQuaternion q;
	q.makeRotate(VecEffector, VecTarget);

	ofMatrix4x4 m;
	m.setRotate(q);
	IkJointsPosition[17] = (IkJointsPosition[17] - IkJointsPosition[16]) * m + IkJointsPosition[16];


	//末端から２つ目の関節
	ofVec3f VecTarget2 = (target - IkJointsPosition[15]).getNormalized();
	ofVec3f VecEffector2 = (IkJointsPosition[17] - IkJointsPosition[15]).getNormalized();

	ofQuaternion q2;
	q2.makeRotate(VecEffector2, VecTarget2);

	ofMatrix4x4 m2;
	m2.setRotate(q2);

	IkJointsPosition[16] = (IkJointsPosition[16] - IkJointsPosition[15]) * m2 + IkJointsPosition[15];
	IkJointsPosition[17] = (IkJointsPosition[17] - IkJointsPosition[15]) * m2 + IkJointsPosition[15];

	//末端から３つ目の関節
	ofVec3f VecTarget3 = (target - IkJointsPosition[14]).getNormalized();
	ofVec3f VecEffector3 = (IkJointsPosition[17] - IkJointsPosition[14]).getNormalized();

	ofQuaternion q3;
	q3.makeRotate(VecEffector3, VecTarget3);

	ofMatrix4x4 m3;
	m3.setRotate(q3);

	IkJointsPosition[15] = (IkJointsPosition[15] - IkJointsPosition[14]) * m3 + IkJointsPosition[14];
	IkJointsPosition[16] = (IkJointsPosition[16] - IkJointsPosition[14]) * m3 + IkJointsPosition[14];
	IkJointsPosition[17] = (IkJointsPosition[17] - IkJointsPosition[14]) * m3 + IkJointsPosition[14];





	//bvh.update();

}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0);

	//cam.begin();
	easycam.begin();
	


	for (int i = 0; i < bvh.getNumJoints(); i++)
	{
		ofSetColor(ofColor::blue);
		ofDrawSphere(IkJointsPosition[i]+(10,10,10), 2);
	}

	bvh.draw();

	ofSetColor(255, 0, 0);
	ofDrawSphere(target, 8);

	
	//cam.end();
	easycam.end();



//	ofSetColor(255);
//	glBegin(GL_LINE_STRIP);
//	for (int i = 0; i < 4; i++) {
//		glVertex3f(joints[i].x, joints[i].y, joints[i].z);
//	}
//	glEnd();
//
//	for (int i = 0; i < 4; i++) {
//		ofDrawCircle(joints[i], 20);
//	}
//
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	if (key == OF_KEY_LEFT) {
		x += -10;
	}

	if (key == OF_KEY_RIGHT) {
		x += 10;
	}

	if (key == OF_KEY_UP) {
		y += 10;
	}

	if (key == OF_KEY_DOWN) {
		y += -10;
	}


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){


	////末端から１つ目の関節
	//ofVec3f VecTarget = (target - joints[2]).getNormalized();
	//ofVec3f VecEffector = (joints[3] - joints[2]).getNormalized();

	//ofQuaternion q;
	//q.makeRotate(VecEffector, VecTarget);

	//ofMatrix4x4 m;
	//m.setRotate(q);
	//joints[3] = (joints[3] - joints[2]) * m + joints[2];


	////末端から２つ目の関節
	//ofVec3f VecTarget2 = (target - joints[1]).getNormalized();
	//ofVec3f VecEffector2 = (joints[3] - joints[1]).getNormalized();

	//ofQuaternion q2;
	//q2.makeRotate(VecEffector2, VecTarget2);

	//ofMatrix4x4 m2;
	//m2.setRotate(q2);

	//joints[2] = (joints[2] - joints[1]) * m2 + joints[1];
	//joints[3] = (joints[3] - joints[1]) * m2 + joints[1];


	////末端から３つ目の関節
	//ofVec3f VecTarget3 = (target - joints[0]).getNormalized();
	//ofVec3f VecEffector3 = (joints[3] - joints[0]).getNormalized();

	//ofQuaternion q3;
	//q3.makeRotate(VecEffector3, VecTarget3);

	//ofMatrix4x4 m3;
	//m3.setRotate(q3);

	//joints[1] = (joints[1] - joints[0]) * m3 + joints[0];
	//joints[2] = (joints[2] - joints[0]) * m3 + joints[0];
	//joints[3] = (joints[3] - joints[0]) * m3 + joints[0];




}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
