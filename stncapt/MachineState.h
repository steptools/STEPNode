/* $RCSfile: MachineState.h,v $
 * $Revision: 1.5 $ $Date: 2016/06/08 21:19:19 $
 * Auth: Sam Bonfante (bonfante@steptools.com)
 * 
 * 	Copyright (c) 1991-2016 by STEP Tools Inc.
 * 	All Rights Reserved
 * 
 * 	This software is furnished under a license and may be used and
 * 	copied only in accordance with the terms of such license and with
 * 	the inclusion of the above copyright notice.  This software and
 * 	accompanying written materials or any other copies thereof may
 * 	not be provided or otherwise made available to any other person.
 * 	No title to or ownership of the software is hereby transferred.
 * 
 * 		----------------------------------------
 */


#pragma once

#include <stixsim_machine_state.h>
#include <RoseString.h>
class stp_machining_workingstep;

class MachineState 
{
private:
    StixSimMachineState _machinestate;
    RoseXform ws_xform;
    RoseStringObject _stringbuff;
    //Keep track if the file gets changed,
    //If true, we need to a save in the destructor.
    bool _fileupdated;
    double _timestep;
    DictionaryOfRoseObject _idtable;
    StixSimDisplayList _prevstate;
    MachineState() {};
public:
    ~MachineState();
    //Gets a new MachineState and sets to the first workingstep.
    static MachineState* InitializeState(const char* filename);
    //Initialize rose stuff.
    static void init();

    RoseStringObject* strbuff() { return &_stringbuff; };

    //Advance MachineState to next workingstep.
    void GoToNextWS();
    //Go forward one timestep in the current workingstep.
    //If we are at the end, go to the next workingstep. Returns 1 if ws is changed, -1 on error, 0 otherwise.
    int AdvanceState();
    //Go To specific workingstep.
    int GoToWS(stp_machining_workingstep* ws);
    //Get Geometry associated with current workingstep.
    int GetGeometryJSON();
    //Get Geometry associated with specific RoseObject.
    int GetGeometryJSON(RoseStringObject id,RoseObject * obj, StixSimGeomType typ);
    //Get Geometry which changed since step or changing workingstep.
    RoseStringObject GetDeltaJSON(bool keyframe);
    //Get the RoseDesign we encapsulate
    RoseDesign* design();
    //Set the Machine used for display purposes.
    //Returns True on success, False on error.
    bool SetMachine(const char* fname);
    //Find any object associated with a known id. Returns null pointer on failure.
    RoseObject* FindObjectByID(const char * id);
    // Functions to get data about the machine state
    void machine_space_coordinates (double x_in, double y_in, double z_in, double &x_out, double &y_out, double &z_out);

};
