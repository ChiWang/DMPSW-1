/*
 *  $Id: DmpBindingKernel.cc, 2014-08-05 19:43:08 DAMPE $
 *  Author(s):
 *    Chi WANG (chiwang@mail.ustc.edu.cn) 07/03/2014
*/

#include <boost/python.hpp>

#include "DmpRootIOSvc.h"
#include "DmpVAlg.h"
#include "DmpAlgorithmManager.h"
#include "DmpServiceManager.h"
#include "DmpCore.h"

//-------------------------------------------------------------------
    // Wrap DmpVAlg
struct DmpVAlgWrapper : public DmpVAlg, boost::python::wrapper<DmpVAlg>{
  DmpVAlgWrapper(const std::string &n):DmpVAlg(n){}
  bool Initialize(){
    return this->get_override("Initialize")();
  }
  bool ProcessThisEvent(){
    return this->get_override("ProcessThisEvent")();
  }
  bool Finalize(){
    return this->get_override("Finalize")();
  }
  /*
  void Set(const std::string &type,const std::string &argv){
    if(boost::python::override Set = this->get_override("Set")(type,argv)){
      Set(type,argv);
    }else{
      DmpVAlg::Set(type,argv);
    }
  }
  void Default_Set(const std::string &type,const std::string &argv){
    this->DmpVAlg::Set(type,argv);
  }
  */
};
    // Wrap DmpVSvc
struct DmpVSvcWrapper : public DmpVSvc, boost::python::wrapper<DmpVSvc>{
  DmpVSvcWrapper(const std::string &n):DmpVSvc(n){}
  bool Initialize(){
    return this->get_override("Initialize")();
  }
  bool Finalize(){
    return this->get_override("Finalize")();
  }
};

//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(SetLogLevel_Wrap,DmpCore::SetLogLevel,1,2)

//-------------------------------------------------------------------
BOOST_PYTHON_MODULE(libDmpKernel){
  using namespace boost::python;
  // DmpVSvc
  class_<DmpVSvcWrapper,boost::noncopyable>("DmpVSvc",init<std::string>())
    .def("Initialize",  pure_virtual(&DmpVSvc::Initialize))
    .def("Finalize",    pure_virtual(&DmpVSvc::Finalize))
    //.def("Set", &DmpVSvc::Set,  &DmpVSvcWrapper::Default_Set)
  ;
  // DmpVAlg
  class_<DmpVAlgWrapper,boost::noncopyable>("DmpVAlg",init<std::string>())
    .def("Initialize",      pure_virtual(&DmpVAlg::Initialize))
    .def("ProcessThisEvent",pure_virtual(&DmpVAlg::ProcessThisEvent))
    .def("Finalize",        pure_virtual(&DmpVAlg::Finalize))
    //.def("Set", &DmpVAlg::Set,  &DmpVAlgWrapper::Default_Set)
  ;
  // DmpAlgorithmManager
  class_<DmpAlgorithmManager,boost::noncopyable>("DmpAlgorithmManager",no_init)
    .def("Append",  &DmpAlgorithmManager::Append)
    .def("Delete",  &DmpAlgorithmManager::Delete)
    .def("Get",     &DmpAlgorithmManager::Get,return_value_policy<reference_existing_object>())
    .def("PrintAllElements",&DmpAlgorithmManager::PrintAllElements)
  ;
  // DmpServiceManager
  class_<DmpServiceManager,boost::noncopyable>("DmpServiceManager",no_init)
    .def("Append",  &DmpServiceManager::Append)
    .def("Delete",  &DmpServiceManager::Delete)
    .def("Get",     &DmpServiceManager::Get,return_value_policy<reference_existing_object>())
    .def("PrintAllElements",&DmpServiceManager::PrintAllElements)
  ;
  // DmpCore
  class_<DmpCore,boost::noncopyable>("DmpCore",no_init)
    .def("GetInstance", &DmpCore::GetInstance,return_value_policy<reference_existing_object>())
    .staticmethod("GetInstance")
    .def("Initialize",  &DmpCore::Initialize)
    .def("Run",         &DmpCore::Run)
    .def("TerminateRun",&DmpCore::TerminateRun)
    .def("Finalize",    &DmpCore::Finalize)
    .def("SetStartTime", &DmpCore::SetStartTime)
    .def("SetStopTime", &DmpCore::SetStopTime)
    .def("SetEventNumber", &DmpCore::SetEventNumber)
    .def("SetLogLevel", &DmpCore::SetLogLevel)
    .def("SetLogHeader", &DmpCore::SetLogHeader)
    .def("AlgorithmManager",    &DmpCore::AlgorithmManager,return_value_policy<reference_existing_object>())
    .def("ServiceManager",      &DmpCore::ServiceManager,return_value_policy<reference_existing_object>())
  ;
  // DmpRootIOSvc
  class_<DmpRootIOSvc,boost::noncopyable,bases<DmpVSvc> >("DmpRootIOSvc",no_init)
    //.def("GetInstance", &DmpRootIOSvc::GetInstance,return_value_policy<reference_existing_object>())
    .def("SetInputPath", &DmpRootIOSvc::SetInputPath)
    .def("SetInputFile", &DmpRootIOSvc::SetInputFile)
    .def("SetOutputPath",&DmpRootIOSvc::SetOutputPath)
    .def("SetOutputFile",&DmpRootIOSvc::SetOutputFile)
    .def("SetWriteList", &DmpRootIOSvc::SetWriteList)
    .def("SetOutFileKey",&DmpRootIOSvc::SetOutFileKey)
    .def("SetFirstInputEvent", &DmpRootIOSvc::SetFirstInputEvent)
  ;

}


