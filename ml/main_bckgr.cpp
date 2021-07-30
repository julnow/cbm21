//#include "AnalysisTree/PlainTreeFiller.hpp"
#include "PFSimpleTask.hpp"
#include <PlainTreeFiller.hpp>

#include "ConverterIn.hpp"
#include "ConverterOut.hpp"

#include "AnalysisTree/TaskManager.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "Wrong number of arguments! Please use:\n  ./main filelist.txt\n";
    return EXIT_FAILURE;
  }

  const bool make_plain_tree{true};

  const std::string& filename = argv[1];


   // ******** no cuts **********************
   Daughter pion_p(211);
   Daughter pion_n(-211);
   Mother kaon(310);
   pion_p.CancelCuts();
   pion_n.CancelCuts();
   kaon.CancelCuts();
   // ***************************************

  Decay kaon_pi_pi("kaon", kaon, {pion_p, pion_n});

  auto* man = AnalysisTree::TaskManager::GetInstance();
  man->SetOutputName("PFSimpleOutput.root", "pTree");

  auto* in_converter = new ConverterIn();
  in_converter->SetTrackCuts(new AnalysisTree::Cuts("Cut to reproduce KFPF", {AnalysisTree::EqualsCut("VtxTracks.pass_cuts", 1)}));
  in_converter->SetIsShine(false);//TODO maybe change name

  auto* pf_task = new PFSimpleTask();
  pf_task->SetInTask(in_converter);
  pf_task->SetDecays({kaon_pi_pi});

  auto* out_converter = new ConverterOut();
  out_converter->SetPFSimpleTask(pf_task);
  out_converter->SetInputBranchNames({"SimParticles", "VtxTracks", "SimEventHeader", "RecEventHeader"});
  out_converter->SetDecay(kaon_pi_pi);

   // AnalysisTree::Cuts* post_cuts = new AnalysisTree::Cuts("post_cuts", {AnalysisTree::RangeCut("Candidates.generation", 0.9, 100)});
   AnalysisTree::Cuts* post_cuts = new AnalysisTree::Cuts("post_cuts", {AnalysisTree::EqualsCut("Candidates.generation", 0)});
//   AnalysisTree::Cuts* post_cuts = new AnalysisTree::Cuts("post_cuts", {AnalysisTree::RangeCut("Candidates.mass", 1.09, 1.14)});
   out_converter->SetOutputCuts(post_cuts);

  man->AddTask(in_converter);
  man->AddTask(pf_task);
  man->AddTask(out_converter);

  man->Init({filename}, {"rTree"});
  man->Run(-1);// -1 = all events
  man->Finish();
  man->ClearTasks();

  if (make_plain_tree) {
    std::ofstream filelist;
    filelist.open("filelist.txt");
    filelist << "PFSimpleOutput.root\n";
    filelist.close();

    man->SetOutputName("PFSimplePlainTree_background.root", "plain_tree");

    //    auto* tree_task_events = new AnalysisTree::PlainTreeFiller();
    //    std::string branchname_events = "Events";
    //    tree_task_events->SetInputBranchNames({branchname_events});
    //    tree_task_events->AddBranch(branchname_events);

    auto* tree_task = new AnalysisTree::PlainTreeFiller();
    std::string branchname_rec = "Candidates";
    tree_task->SetInputBranchNames({branchname_rec});
    tree_task->AddBranch(branchname_rec);

    man->AddTask(tree_task);

    man->Init({"filelist.txt"}, {"pTree"});
    man->Run(-1);// -1 = all events
    man->Finish();
  }

  return EXIT_SUCCESS;
}
