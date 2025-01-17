/*
#  Copyright(C) 2015-2018  all rights reserved

#  This program is a free software; you can redistribute it and / or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
#  GNU General Public License for more details.
#
#  A copy of the GNU General Public License is available at
#  http://www.gnu.org/Licenses/
*/

#pragma once
#include "Constants.h"
#include<string>
#include<sstream>
#include<vector>
#include<stdlib.h>
#include<map>
#include<algorithm>
#include<math.h>
using namespace std;

class PepAttributeWorker
{
public:
	PepAttributeWorker();
	vector<string> mf_LoadAAindex();
	~PepAttributeWorker(void);
	void mf_showAAindexValue(string path);

	vector<double>  mf_GetAttributeFromSequence(string Sequence, string SequenceWithFlankingRegion);

	/*----------------APEX Tool 35 peptide properties------------------------*/
	int mf_getLength(string seqChars);
	double mf_getMass(string seqChars);
	vector<double> mf_getAAFrequencies(string seqChars, string aaSymbols);
	int mf_GetMissingCleavageNumber(string seqChars);

	double mf_computeNetCharge(string seqChars, double pH);
	int mf_getSumNeutralResidues(string seqChars);
	int mf_getSumBasicResidues(string seqChars);

	double mf_computeProportionLargeSizedResidues(string seqChars);
	double mf_computeProportionSmallSizedResidues(string seqChars);

	/*-----------------------haixu tang----------------------------*/
	double mf_getMass2LengthRatio(string seqChars);
	double mf_computeSequenceComplexity(vector<double> aaFrequencies);//based on the function vector<double> getAAFrequencies(string seqChars,string aaSymbols);

	//below are the functions in which I reimplement which are originally in Matlab
	double mf_getVihinenFlexibility(string seqChars);//finished
	double mf_getHydrophobicMoment(string seqChars, double window, double angle);//finished
	double mf_getBFactorPrediction(string seqChars, int Win, int Wout);
	vector<double> mf_getVL2Disorder(string seqChars);//Actually there are 4 predictors in this function: VL2, VL2V, VL2C, VL2S

	//these functions are the ones that I write to simulate the corresponding functions in Matlab used by the functions above
	void mf_filter(int ord, double *a, double *b, int np, double *x, double *y);
	void mf_filter_twosided(double **matrix_protein, int matrixRow, int matrixColumn, double * filt_onesided, int filtOnesidedSize);
	void mf_filter_error(double **pfilt, int pfiltRow, int pfiltColumn, double *data, int dataLength, double *filt_onesided, int filtOnesidedSize);
	void mf_predictLinear(string seqChars, double **pfilt, int pfiltRow, int pfiltColumn);
	void mf_proteinFlatFilter(double **matrix_protein, int matrixRow, int matrixColumn, string sequence, double * filt_onesided, int filtOnesidedSize);//try
	void mf_moving_average(double *x, int window, double * y, int length);
	void mf_makeAttribute(double **data, int dataRow, int dataColumn, string sequence, int W_IN);
	void mf_filter_prot(double *pred, double **pfilt, int pfiltRow, int pfiltColumn, double *filt_onesided, int filtOnesidedSize);

	/*------------SVM all of these 4 functions have been implemented ------------------*/
	int mf_getNumberNonPolarHydrophobicResidues(string seqChars);
	int mf_getNumberPolarHydrophilicResidues(string seqChars);
	int mf_getNumberUnchargedPolarHydrophilicResidues(string seqChars);
	int mf_getNumberChargedPolarHydrophilicResidues(string seqChars);

private:
	Constants m_constants;
	double m_arrayAAindexAttributeValue[544][20];
	bool m_arrayIfIndexAttributeExist[544][20];
	vector<int> mf_Sequence2Index(string Sequence);
	string m_strAAindexFilePath;
};
class CPeptideAttribute
{
public:
	vector<double> m_vecFeatures;

	void Clear()
	{
		m_vecFeatures.clear();
	}
	friend ostream& operator <<(ostream &, CPeptideAttribute peptideAttribute);

};
