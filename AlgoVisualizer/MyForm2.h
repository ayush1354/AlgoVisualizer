#pragma once
#include "MyForm2.h"
#include <random>
#include <iostream>
#include <sstream>

namespace AlgoVisualizer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;


	/// <summary>
	/// Summary for MyForm2
	/// </summary>
	public ref class MyForm2 : public System::Windows::Forms::Form
	{
	public:
		System::Collections::Generic::List<Label^>^ labelArray;
		System::Collections::Generic::List<int>^ arr;
		String^ algoName;
		MyForm2(String^ algoName, System::Collections::Generic::List<int>^ arr)
		{
			this->arr = arr;
			this->algoName = algoName;
			this->targetBox = targetBox;
			labelArray = gcnew System::Collections::Generic::List<Label^>();
			timer = gcnew System::Windows::Forms::Timer();
			moveTimer = gcnew System::Windows::Forms::Timer();
			timer->Interval = 25;
			moveTimer->Interval = 25;
			timer->Tick += gcnew System::EventHandler(this, &MyForm2::timer_Tick);
			moveTimer->Tick += gcnew System::EventHandler(this, &MyForm2::move_tick);
			InitializeComponent(algoName);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm2()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Timer^ timer;
		System::Windows::Forms::Timer^ moveTimer;
		bool isSwapping = false;
		bool movingUp = false;
		Label^ label1;
		Label^ label2;
		Label^ labelToMove;
		Point finalPos;
		System::Drawing::Point p1;
		System::Drawing::Point p2;
		TextBox^ targetBox;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(String^ title)
		{
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(960, 540);
			this->Text = title;
			int currPos = 50;
			for each (int i in arr) {
				Label^ myLabel = gcnew Label();
				myLabel->Text = i.ToString();
				myLabel->Location = Point(currPos, 50);
				myLabel->AutoSize = false;
				myLabel->BackColor = System::Drawing::Color::Yellow;
				myLabel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				myLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
				myLabel->TextAlign = ContentAlignment::MiddleCenter;
				myLabel->Size = System::Drawing::Size(30, 30);
				currPos += 50;
				this->labelArray->Add(myLabel);
				this->Controls->Add(myLabel);
			}

			Button^ startBtn = gcnew Button();
			startBtn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			startBtn->Location = System::Drawing::Point(400, 400);
			startBtn->Name = L"startBtn";
			startBtn->Size = System::Drawing::Size(160, 40);
			startBtn->TabIndex = 3;
			startBtn->Text = L"Start";
			startBtn->UseVisualStyleBackColor = true;
			startBtn->Click += gcnew System::EventHandler(this, &MyForm2::start);
			this->Controls->Add(startBtn);

		}
#pragma endregion

		void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
			int step = 1;
			int multiplyer = 1;
			if (label1->Location.X != p2.X) {
				if (label1->Location.X > p2.X) multiplyer = -1;
				label1->Location = System::Drawing::Point(label1->Location.X + step * multiplyer, label1->Location.Y);
			}
			else if (label2->Location.X != p1.X) {
				if (label2->Location.X > p1.X) multiplyer = -1;
				label2->Location = System::Drawing::Point(label2->Location.X + step * multiplyer, label1->Location.Y);
			}
			else {
				isSwapping = false;
				timer->Stop();
			}

		}

		void move_tick(System::Object^ sender, System::EventArgs^ e) {
			int step = 1;
			int xMul = 1;
			int yMul = 1;

			if (labelToMove->Location.X != finalPos.X) {
				if (labelToMove->Location.X > finalPos.X) xMul = -1;
				labelToMove->Location = System::Drawing::Point(labelToMove->Location.X + step * xMul, labelToMove->Location.Y);
			}
			else if (labelToMove->Location.Y != finalPos.Y) {
				if (labelToMove->Location.Y > finalPos.Y) yMul = -1;
				labelToMove->Location = Point(labelToMove->Location.X, labelToMove->Location.Y + step * yMul);
			}
			else {
				movingUp = false;
				moveTimer->Stop();
			}
		}

	private: System::Void start(System::Object^ sender, System::EventArgs^ e) {
		int n = arr->Count;
		if (algoName->Equals("Bubble Sort")) {
			for (int i = 0;i < n;i++) {
				bool swaped = false;
				for (int j = 0;j < n - i - 1;j++) {
					if (arr[j] > arr[j + 1]) {
						swap(arr, j, j + 1);
						isSwapping = true;
						while (isSwapping)
						{
							Application::DoEvents();
						}
						label1->BackColor = System::Drawing::Color::Yellow;
						label2->BackColor = System::Drawing::Color::Yellow;
						swaped = true;
					}
					else
					{
						label1 = labelArray[j + 1];
						label2 = labelArray[j];
						label1->BackColor = System::Drawing::Color::LightGreen;
						label2->BackColor = System::Drawing::Color::LightGreen;
						DateTime startTime = DateTime::Now;
						while ((DateTime::Now - startTime).TotalMilliseconds < 1000) {
							Application::DoEvents();
						}

						label1->BackColor = System::Drawing::Color::Yellow;
						label2->BackColor = System::Drawing::Color::Yellow;
						startTime = DateTime::Now;
						while ((DateTime::Now - startTime).TotalMilliseconds < 500) {
							Application::DoEvents();
						}
					}
				}
				if (!swaped) break;
			}
		}
		else if (algoName->Equals("Selection Sort")) {
			Label^ minLabel = gcnew Label();
			minLabel->Text = "Min";
			minLabel->Location = Point(labelArray[0]->Location.X, labelArray[0]->Location.Y);
			minLabel->AutoSize = false;
			minLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			minLabel->TextAlign = ContentAlignment::MiddleLeft;
			minLabel->Size = System::Drawing::Size(30, 30);
			this->Controls->Add(minLabel);
			for (int i = 0;i < n;i++) {
				int minIndex = i;
				minLabel->Location = Point(labelArray[minIndex]->Location.X, labelArray[minIndex]->Location.Y + 50);
				for (int j = i;j < n;j++) {
					label1 = labelArray[j];
					label2 = labelArray[minIndex];
					label1->BackColor = System::Drawing::Color::LightGreen;
					label2->BackColor = System::Drawing::Color::LightGreen;
					DateTime startTime = DateTime::Now;
					while ((DateTime::Now - startTime).TotalMilliseconds < 1000) {
						Application::DoEvents();
					}
					label1->BackColor = System::Drawing::Color::Yellow;
					label2->BackColor = System::Drawing::Color::Yellow;
					if (arr[j] < arr[minIndex]) {
						minIndex = j;
						minLabel->Location = Point(labelArray[minIndex]->Location.X, labelArray[minIndex]->Location.Y + 50);
					}
				}
				if (minIndex != i) {
					swap(arr, i, minIndex);
					isSwapping = true;
					minLabel->Visible = false;
					while (isSwapping)
					{
						Application::DoEvents();
					}
					minLabel->Visible = true;
					label1->BackColor = System::Drawing::Color::Yellow;
					label2->BackColor = System::Drawing::Color::Yellow;
				}
			}
			minLabel->Visible = false;
		}
		else if (algoName->Equals("Insertion Sort")) {
			for (int i = 1;i < n;i++) {
				int temp = arr[i];
				Label^ tempLabel = labelArray[i];
				tempLabel->BackColor = System::Drawing::Color::LightGreen;
				labelToMove = tempLabel;
				Point locToGoTo = labelToMove->Location;
				finalPos = Point(labelToMove->Location.X, labelToMove->Location.Y + 50);
				moveTimer->Start();
				movingUp = true;
				while (movingUp)
				{
					Application::DoEvents();
				}
				int empty = 0;
				bool swaped = false;
				for (int j = i - 1;j >= 0;j--) {
					if (arr[j] > temp) {
						arr[j + 1] = arr[j];
						locToGoTo = labelArray[j]->Location;
						labelToMove = labelArray[j];
						labelToMove->BackColor = System::Drawing::Color::LightGreen;
						DateTime startTime = DateTime::Now;
						while ((DateTime::Now - startTime).TotalMilliseconds < 500) {
							Application::DoEvents();
						}
						finalPos = Point(labelToMove->Location.X + 50, labelToMove->Location.Y);
						moveTimer->Start();
						movingUp = true;
						while (movingUp)
						{
							Application::DoEvents();
						}
						labelToMove->BackColor = System::Drawing::Color::Yellow;
						labelArray[j + 1] = labelArray[j];
						swaped = true;
						empty = j;
					}
					else {
						DateTime startTime = DateTime::Now;
						while ((DateTime::Now - startTime).TotalMilliseconds < 500) {
							Application::DoEvents();
						}
						labelToMove = tempLabel;
						finalPos = locToGoTo;
						moveTimer->Start();
						movingUp = true;
						while (movingUp)
						{
							Application::DoEvents();
						}
						break;
					}
				}
				if (swaped) {
					arr[empty] = temp;
					labelToMove = tempLabel;
					finalPos = locToGoTo;
					moveTimer->Start();
					movingUp = true;
					while (movingUp)
					{
						Application::DoEvents();
					}
					labelArray[empty] = tempLabel;
				}
				tempLabel->BackColor = System::Drawing::Color::Yellow;
			}
		}
		else if (algoName->Equals("Merge Sort")) {
			mergeSort(arr, 0, n - 1);
		}
		else if (algoName->Equals("Quick Sort")) {
			Label^ jLabel = gcnew Label();
			jLabel->Text = "i";
			jLabel->Location = Point(labelArray[0]->Location.X, labelArray[0]->Location.Y);
			jLabel->AutoSize = false;
			jLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			jLabel->TextAlign = ContentAlignment::MiddleLeft;
			jLabel->Size = System::Drawing::Size(30, 30);
			jLabel->BackColor = Color::Transparent;
			this->Controls->Add(jLabel);
			Label^ iLabel = gcnew Label();
			iLabel->Text = "j";
			iLabel->Location = Point(labelArray[0]->Location.X, labelArray[0]->Location.Y);
			iLabel->AutoSize = false;
			iLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			iLabel->TextAlign = ContentAlignment::MiddleLeft;
			iLabel->Size = System::Drawing::Size(30, 30);
			iLabel->BackColor = Color::Transparent;
			this->Controls->Add(iLabel);
			Label^ pivotLabel = gcnew Label();
			pivotLabel->Text = "pivot";
			pivotLabel->Location = Point(labelArray[0]->Location.X, labelArray[0]->Location.Y);
			pivotLabel->AutoSize = false;
			pivotLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			pivotLabel->TextAlign = ContentAlignment::MiddleLeft;
			pivotLabel->Size = System::Drawing::Size(60, 30);
			this->Controls->Add(pivotLabel);
			QuickSort(arr, 0, n - 1, iLabel, jLabel, pivotLabel);
			for (int i = 0;i < n;i++) {
				Debug::WriteLine(arr[i]);
			}
			this->Controls->Remove(iLabel);
			this->Controls->Remove(jLabel);
			this->Controls->Remove(pivotLabel);
		}
		else if (algoName->Equals("Binary Search")) {
			// Visualization logic for Binary Search
			int target = Int32::Parse(targetBox->Text); // Assuming targetBox contains the target value
			binarySearchVisualization(arr, 0, arr->Count - 1, target);
	}
}



		   void QuickSort(System::Collections::Generic::List<int>^ arr, int left, int right, Label^ iLabel, Label^ jLabel, Label^ pivotLabel) {
			   if (left < right) {
				   int pivot = partition(arr, left, right, iLabel, jLabel, pivotLabel);
				   QuickSort(arr, left, pivot - 1, iLabel, jLabel, pivotLabel);
				   QuickSort(arr, pivot + 1, right, iLabel, jLabel, pivotLabel);
			   }
		   }

		   int partition(System::Collections::Generic::List<int>^ arr, int left, int right, Label^ iLabel, Label^ jLabel, Label^ pivotLabel) {
			   int pivot = arr[left];
			   int i = left;
			   int j = right;
			   Debug::WriteLine(i+" "+j);
			   pivotLabel->Location = Point(labelArray[left]->Location.X, labelArray[left]->Location.Y - 30);
			   jLabel->Location = Point(labelArray[i]->Location.X, labelArray[i]->Location.Y+30);
			   iLabel->Location = Point(labelArray[j]->Location.X, labelArray[j]->Location.Y+30);
			   while (i < j)
			   {
				   while (arr[i] <= pivot && i < right) {
					   i++;
					   jLabel->Location = Point(labelArray[i]->Location.X, labelArray[i]->Location.Y + 30);//idk why tf i have to set jlabel position as ith index peice of shit this is. shit code shit project idk why the fuck i am doing this. i want to throw my laptop on the ground and fo and drink cold coffee or smthing i hatge this shit but uk i like ot suffer so i will continuw this ig:)
					   if (jLabel->Location == iLabel->Location) jLabel->Location = Point(jLabel->Location.X + 15, jLabel->Location.Y);
					   labelArray[i]->BackColor = System::Drawing::Color::LightGreen;
					   labelArray[left]->BackColor = System::Drawing::Color::LightGreen;
					   wait(1000);
					   labelArray[i]->BackColor = System::Drawing::Color::Yellow;
					   labelArray[left]->BackColor = System::Drawing::Color::Yellow;
				   }
				   while (arr[j] > pivot) {
					   j--;
					   iLabel->Location = Point(labelArray[j]->Location.X, labelArray[j]->Location.Y + 30);
					   if (jLabel->Location == iLabel->Location) jLabel->Location = Point(jLabel->Location.X + 15, jLabel->Location.Y);
					   labelArray[j]->BackColor = System::Drawing::Color::LightGreen;
					   labelArray[left]->BackColor = System::Drawing::Color::LightGreen;
					   wait(1000);
					   labelArray[j]->BackColor = System::Drawing::Color::Yellow;
					   labelArray[left]->BackColor = System::Drawing::Color::Yellow;
				   }
				   if (i < j) {
					   swap(arr, i, j);
					   isSwapping = true;
					   while (isSwapping)
					   {
						   Application::DoEvents();
						   this->Controls->Remove(iLabel);
						   this->Controls->Remove(jLabel);
						   this->Controls->Remove(pivotLabel);
					   }
					   this->Controls->Add(iLabel);
					   this->Controls->Add(jLabel);
					   this->Controls->Add(pivotLabel);
					   label1->BackColor = System::Drawing::Color::Yellow;
					   label2->BackColor = System::Drawing::Color::Yellow;
				   }
			   }
			   swap(arr, left, j);
			   isSwapping = true;
			   while (isSwapping)
			   {
				   Application::DoEvents();
				   this->Controls->Remove(iLabel);
				   this->Controls->Remove(jLabel);
				   this->Controls->Remove(pivotLabel);
			   }
			   this->Controls->Add(iLabel);
			   this->Controls->Add(jLabel);
			   this->Controls->Add(pivotLabel);
			   label1->BackColor = System::Drawing::Color::Yellow;
			   label2->BackColor = System::Drawing::Color::Yellow;
			   return j;
		   }

		   void mergeSort(System::Collections::Generic::List<int>^ arr, int const left, int const right)
		   {
			   if (left < right) {
				   int mid = (left + right) / 2;
				   mergeSort(arr, left, mid);
				   for (int i = left;i < mid;i++) {
					   int red = std::rand() % 256;  // Random value between 0 and 255
					   int green = std::rand() % 256;
					   int blue = std::rand() % 256;
					   //labelArray[i]->BackColor = System::Drawing::Color::FromArgb(red, green, blue);
				   }
				   mergeSort(arr, mid + 1, right);
				   for (int i = mid;i < right;i++) {
					   int red = std::rand() % 256;  // Random value between 0 and 255
					   int green = std::rand() % 256;
					   int blue = std::rand() % 256;
					   //labelArray[i]->BackColor = System::Drawing::Color::FromArgb(red, green, blue);
				   }
				   merge(arr, left, mid, right);
			   }
		   }
		   
		   void AlgoVisualizer::MyForm2::binarySearchVisualization(System::Collections::Generic::List<int>^ arr, int left, int right, int target) {
			   int low = left;
			   int high = right;
			   while (low <= high) {
				   int mid = low + (high - low) / 2;

				   // Visualization code for comparison
				   labelArray[mid]->BackColor = System::Drawing::Color::Aqua;
				   wait(1000); // Delay to visualize the comparison
				   labelArray[mid]->BackColor = System::Drawing::Color::Yellow;

				   if (arr[mid] == target) {
					   // Visualization code for target found
					   labelArray[mid]->BackColor = System::Drawing::Color::Green;
					   return;
				   }
				   else if (arr[mid] < target) {
					   // Visualization code for adjusting low
					   low = mid + 1;
					   for (int i = left; i <= mid; i++) {
						   labelArray[i]->BackColor = System::Drawing::Color::Yellow;
					   }
				   }
				   else {
					   // Visualization code for adjusting high
					   high = mid - 1;
					   for (int i = mid; i <= right; i++) {
						   labelArray[i]->BackColor = System::Drawing::Color::Yellow;
					   }
				   }
			   }

			   // Visualization code for target not found
			   labelArray[low]->BackColor = System::Drawing::Color::Red;
		   }

		   


		   void merge(System::Collections::Generic::List<int>^ arr, int l, int mid, int r)
		   {
			   for (int x = l;x <= r;x++) {
				   labelArray[x]->BackColor = System::Drawing::Color::Aqua;
			   }

			   wait(1000);

			   System::Collections::Generic::List<int>^ arr2 = gcnew System::Collections::Generic::List<int>(r + 1);
			   int i = l;
			   int j = mid + 1;
			   int curr = l;

			   while (j <= r && i <= mid) {
				   if (arr[i] < arr[j]) {
					   arr2->Add(arr[i]); // Use Add to add elements to the List
					   i++;
				   }
				   else {
					   arr2->Add(arr[j]); // Use Add to add elements to the List
					   j++;
				   }
				   curr++;
			   }

			   while (i <= mid) {
				   arr2->Add(arr[i]); // Add remaining elements from the left subarray
				   i++;
				   curr++;
			   }

			   while (j <= r) {
				   arr2->Add(arr[j]); // Add remaining elements from the right subarray
				   j++;
				   curr++;
			   }

			   // Copy elements back to the original array 'arr'
			   for (int k = l; k <= r; k++) {
				   arr[k] = arr2[k - l]; // Subtract 'l' to map the index correctly

			   }

			   for (int x = l;x <= r;x++) {
				   labelArray[x]->BackColor = System::Drawing::Color::Yellow;
			   }

		   }

		   int AlgoVisualizer::MyForm2::binarySearch(int target) {
			   int left = 0;
			   int right = arr->Count - 1;

			   while (left <= right) {
				   int mid = left + (right - left) / 2;

				   // Visualization code for comparison
				   labelArray[mid]->BackColor = System::Drawing::Color::Aqua;
				   wait(1000); // Delay to visualize the comparison
				   labelArray[mid]->BackColor = System::Drawing::Color::Yellow;

				   // Check if the target is present at the middle
				   if (arr[mid] == target) {
					   // Visualization code for target found
					   labelArray[mid]->BackColor = System::Drawing::Color::Green;
					   return mid;
				   }
				   // If the target is greater, ignore the left half
				   if (arr[mid] < target) {
					   left = mid + 1;
					   for (int i = 0; i < left; i++) {
						   labelArray[i]->BackColor = System::Drawing::Color::Yellow;
					   }
				   }
				   // If the target is smaller, ignore the right half
				   else {
					   right = mid - 1;
					   for (int i = right + 1; i < arr->Count; i++) {
						   labelArray[i]->BackColor = System::Drawing::Color::Yellow;
					   }
				   }
			   }

			   // Target was not found in the list
			   return -1;
		   }


		   void wait(int n) {
			   DateTime startTime = DateTime::Now;
			   while ((DateTime::Now - startTime).TotalMilliseconds < n) {
				   Application::DoEvents();
			   }
		   }

		   void swap(System::Collections::Generic::List<int>^ arr, int i, int j) {
			   int temp = arr[i];
			   arr[i] = arr[j];
			   arr[j] = temp;
			   label1 = labelArray[i];
			   label2 = labelArray[j];
			   label1->BackColor = System::Drawing::Color::LightGreen;
			   label2->BackColor = System::Drawing::Color::LightGreen;
			   wait(500);
			   p1 = label1->Location;
			   p2 = label2->Location;
			   Label^ tempLabel = labelArray[i];
			   labelArray[i] = labelArray[j];
			   labelArray[j] = tempLabel;
			   timer->Start();
		   }

		   void waitTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
			   System::Windows::Forms::Timer^ waitTimer = static_cast<System::Windows::Forms::Timer^>(sender);
			   waitTimer->Stop();
		   }
	};
}