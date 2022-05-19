from sklearn.metrics import f1_score
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import random
import csv
import re
import argparse

sns.set()
# Will be true when running in Kaggle, false otherwise
use_kaggle_filepaths = os.environ.get("KAGGLE_DATA_PROXY_TOKEN") is not None

if use_kaggle_filepaths:
    train_filepath = "/kaggle/input/tweet-sentiment-extraction/train.csv"
    test_filepath = "/kaggle/input/tweet-sentiment-extraction/test.csv"
    output_filepath = "/kaggle/working/submission.csv"
    svm_joblib_filepath = "/kaggle/input/svcprobabiltiytrainedjoblibtweetextraction/v0.0.2p.joblib"
    neural_joblib_filepath = "/kaggle/input/svcprobabiltiytrainedjoblibtweetextraction/v0.0.2p.joblib"
else:
    train_filepath = "./data/train.csv"
    test_filepath = "./data/test.csv"
    output_filepath = "./data/output.csv"
    svm_joblib_filepath = "./svm/v0.0.2p.joblib"
    neural_joblib_filepath = "./neural/v0.0.0m.joblib"



def load_args():

    parser = argparse.ArgumentParser(description='arguments')
    parser.add_argument('--county_dict', default=1, type=int)
    parser.add_argument('--decision_tree', default=1, type=int)
    parser.add_argument('--random_forest', default=1, type=int)
    parser.add_argument('--root_dir', default='./data/', type=str)
    args = parser.parse_args()

    return args


def county_info(args):
    county_dict = load_dictionary(args.root_dir)
    dictionary_info(county_dict)


def decision_tree_testing(x_train, y_train, x_test, y_test):
    print('Decision Tree\n\n')
    clf = DecisionTreeClassifier(max_depth=5)
    clf.fit(x_train, y_train)
    preds_train = clf.predict(x_train)
    preds_test = clf.predict(x_test)
    train_accuracy = accuracy_score(preds_train, y_train)
    test_accuracy = accuracy_score(preds_test, y_test)
    print('Train {}'.format(train_accuracy))
    print('Test {}'.format(test_accuracy))
    preds = clf.predict(x_test)
    print('F1 Test {}'.format(f1(y_test, preds)))


def random_forest_testing(x_train, y_train, x_test, y_test):
    print('Random Forest\n\n')
    rclf = RandomForestClassifier(max_depth=5, max_features=10, n_trees=100)
    rclf.fit(x_train, y_train)
    preds_train = rclf.predict(x_train)
    preds_test = rclf.predict(x_test)
    train_accuracy = accuracy_score(preds_train, y_train)
    test_accuracy = accuracy_score(preds_test, y_test)
    print('Train {}'.format(train_accuracy))
    print('Test {}'.format(test_accuracy))
    preds = rclf.predict(x_test)
    print('F1 Test {}'.format(f1(y_test, preds)))


def create_trees(x_train, y_train, x_test, y_test):
    train = []
    test = []
    y = []
    for i in range(1, 26):
        y.append(i)
        print("LENGTH: ", i)
        h = DecisionTreeClassifier(max_depth=i)
        h.fit(x_train, y_train)
        preds_train = h.predict(x_train)
        preds_test = h.predict(x_test)
        train_accuracy = accuracy_score(preds_train, y_train)
        train.append(train_accuracy)
        test_accuracy = accuracy_score(preds_test, y_test)
        test.append(test_accuracy)
        print('Train {}'.format(train_accuracy))
        print('Test {}'.format(test_accuracy))
        preds = h.predict(x_test)
        print('F1 Test {}'.format(f1(y_test, preds)))
    return y, train, test

def clean_text(text):

    # remove HTML tags
    text = re.sub(r'<.*?>', '', text)

    # remove the characters [\], ['] and ["]
    text = re.sub(r"\\", "", text)
    text = re.sub(r"\'", "", text)
    text = re.sub(r"\"", "", text)
    # pattern = r'[^a-zA-z0-9\s]'
    # text = re.sub(pattern, '', text)

    # convert text to lowercase
    text = text.strip().lower()

    # replace punctuation characters with spaces
    filters = '!"\'#$%&()+,-./:;<=>?@[\\]^_`{|}~\t\n'
    translate_dict = dict((c, "") for c in filters)
    translate_map = str.maketrans(translate_dict)
    text = text.translate(translate_map)

    return text.split()

def word_classify(text, imptext, mood, baseW, impW):
    word_list = []
    test = open("./data/x_train.csv", mode='w', encoding='UTF-8', newline='')
    csvwriter = csv.writer(test)

    for comment in imptext:
        for word in comment:
            flag = 1
            for elem in word_list:
                if elem == word:
                    flag = 0
                    break
            if flag:
                word_list.append(word)
    for i in range(len(text)):
        str = [0]*len(word_list)
        for word in text[i]:
            for j in range(len(word_list)):
                if word == word_list[j]:
                    str[j] += baseW
                    break
        for word in imptext[i]:
            for j in range(len(word_list)):
                if word == word_list[j]:
                    str[j] += impW
                    break
        csvwriter.writerow(str)

    test.close()
    test = open("./data/y_train.csv", mode='w', encoding='UTF-8', newline='')
    csvYwriter = csv.writer(test)
    for value in mood:
        csvYwriter.writerow([value])
    test.close()

    return word_list


def test_classify(words, text, tmood, baseW):
    test = open("./data/x_test.csv", mode='w', encoding='UTF-8', newline='')
    csvwriter = csv.writer(test)
    for i in range(len(text)):
        str = [0]*len(words)
        for word in text[i]:
            for j in range(len(words)):
                if word == words[j]:
                    str[j] += baseW
                    break
        csvwriter.writerow(str)
    test.close()
    test = open("./data/y_test.csv", mode='w', encoding='UTF-8', newline='')
    csvYwriter = csv.writer(test)
    for value in tmood:
        csvYwriter.writerow([value])

    test.close()

    return


###################################################
# Modify for running your experiments accordingly #
###################################################
if __name__ == '__main__':

    f = open("./data/train.csv", mode='r')
    csvF = csv.reader(f)
    textID = []
    text = []
    textSel = []
    mood = []
    for line in csvF:
        textID.append(line[0])
        text.append(clean_text(line[1]))
        textSel.append(clean_text(line[2]))
        mood.append(line[3])
    f.close()
    intmood = [0]*len(mood)

    for i in range(len(mood)):
        if mood[i] == "positive" or mood[i] == "neutral":
            intmood[i] = 1
        elif mood[i] == "negative":
            intmood[i] = -1

    # print(intmood)

    f = open("./data/test.csv", mode='r')
    tcsvF = csv.reader(f)
    ttextID = []
    ttext = []
    tmood = []
    for line in tcsvF:
        ttextID.append(line[0])
        ttext.append(clean_text(line[1]))
        tmood.append(line[2])

    tintmood = [0] * len(tmood)
    for i in range(len(tmood)):
        if tmood[i] == "positive" or tmood[i] == "neutral":
            tintmood[i] = 1
        elif tmood[i] == "negative":
            tintmood[i] = -1
    # print(tmood)

    words = word_classify(text[1:], textSel[1:], intmood, 1, 5)
    test_milled = test_classify(words, ttext[1:], tintmood, 1)
    args = load_args()
    print("building tree")
    x_train, y_train, x_test, y_test = load_data(args.root_dir)
    decision_tree_testing(x_train, y_train, x_test, y_test)

    '''
	inp = ""
	while inp != "done!":
		inp = input("what should i search for?")
		for i in milled:
			if i[0] == inp:
				print(i)
	'''
    print('Done')


class Node():
    """
    Node of decision tree

    Parameters:
    -----------
    prediction: int
            Class prediction at this node
    feature: int
            Index of feature used for splitting on
    split: int
            Categorical value for the threshold to split on for the feature
    left_tree: Node
            Left subtree
    right_tree: Node
            Right subtree
    """

    def __init__(self, prediction, feature, split, left_tree, right_tree):
        self.prediction = prediction
        self.feature = feature
        self.split = split
        self.left_tree = left_tree
        self.right_tree = right_tree


class DecisionTreeClassifier():
    """
    Decision Tree Classifier. Class for building the decision tree and making predictions

    Parameters:
    ------------
    max_depth: int
            The maximum depth to build the tree. Root is at depth 0, a single split makes depth 1 (decision stump)
    """

    def __init__(self, max_depth=None):
        self.max_depth = max_depth

    # take in features X and labels y
    # build a tree
    def fit(self, X, y):
        self.num_classes = len(set(y))
        self.root = self.build_tree(X, y, depth=1)

    # make prediction for each example of features X
    def predict(self, X):
        preds = [self._predict(example) for example in X]

        return preds

    # prediction for a given example
    # traverse tree by following splits at nodes
    def _predict(self, example):
        node = self.root
        while node.left_tree:
            if example[node.feature] < node.split:
                node = node.left_tree
            else:
                node = node.right_tree
        return node.prediction

    # accuracy
    def accuracy_score(self, X, y):
        preds = self.predict(X)
        accuracy = (preds == y).sum()/len(y)
        return accuracy

    # function to build a decision tree
    def build_tree(self, X, y, depth, features=0):
        num_samples, num_features = X.shape
        # which features we are considering for splitting on

        self.features_idx = np.arange(0, X.shape[1])

        # store data and information about best split
        # used when building subtrees recursively
        best_feature = None
        best_split = None
        best_gain = 0.0
        best_left_X = None
        best_left_y = None
        best_right_X = None
        best_right_y = None

        # what we would predict at this node if we had to
        # majority class
        num_samples_per_class = [np.sum(y == i)
                                 for i in range(self.num_classes)]
        prediction = np.argmax(num_samples_per_class)

        # if we haven't hit the maximum depth, keep building
        if depth <= self.max_depth:
            # consider each feature
            if features != 0:
                # generate list of max_features
                kept_features = set([])
                while len(kept_features) < features:
                    # random number between 0 and 50
                    kept_features.add(random.randint(0, X.shape[1]-1))
                self.features_idx = kept_features

            for feature in self.features_idx:
                # consider the set of all values for that feature to split on
                possible_splits = np.unique(X[:, feature])
                for split in possible_splits:
                    # get the gain and the data on each side of the split
                    # >= split goes on right, < goes on left
                    gain, left_X, right_X, left_y, right_y = self.check_split(
                        X, y, feature, split)
                    # if we have a better gain, use this split and keep track of data
                    if gain > best_gain:
                        best_gain = gain
                        best_feature = feature
                        best_split = split
                        best_left_X = left_X
                        best_right_X = right_X
                        best_left_y = left_y
                        best_right_y = right_y

        # if we haven't hit a leaf node
        # add subtrees recursively
        if best_gain > 0.0:
            left_tree = self.build_tree(
                best_left_X, best_left_y, depth=depth+1)
            right_tree = self.build_tree(
                best_right_X, best_right_y, depth=depth+1)
            return Node(prediction=prediction, feature=best_feature, split=best_split, left_tree=left_tree, right_tree=right_tree)

        # if we did hit a leaf node
        return Node(prediction=prediction, feature=best_feature, split=best_split, left_tree=None, right_tree=None)

    # gets data corresponding to a split by using numpy indexing

    def check_split(self, X, y, feature, split):
        left_idx = np.where(X[:, feature] < split)
        right_idx = np.where(X[:, feature] >= split)
        left_X = X[left_idx]
        right_X = X[right_idx]
        left_y = y[left_idx]
        right_y = y[right_idx]

        # calculate gini impurity and gain for y, left_y, right_y
        gain = self.calculate_gini_gain(y, left_y, right_y)
        return gain, left_X, right_X, left_y, right_y

    def calculate_gini_gain(self, y, left_y, right_y):
        # not a leaf node
        # calculate gini impurity and gain
        gain = 0

        if len(left_y) > 0 and len(right_y) > 0:

            ########################################
            #       YOUR CODE GOES HERE            #
            ########################################
            c_plus = 0
            c_minus = 0
            cl_plus = 0
            cl_minus = 0
            cr_plus = 0
            cr_minus = 0
            pl = 0
            pr = 0

            for i in range(0, len(y)):
                if y[i] == 1:
                    c_plus += 1
                else:
                    c_minus += 1
            t1 = (c_plus / (c_plus + c_minus))
            t2 = (c_minus / (c_plus + c_minus))
            u_y = 1 - (t1 ** 2) - (t2 ** 2)
            for j in range(0, len(left_y)):
                if left_y[j] == 1:
                    cl_plus += 1
                else:
                    cl_minus += 1
            t1 = (cl_plus / (cl_plus + cl_minus))
            t2 = (cl_minus / (cl_plus + cl_minus))
            u_left_y = 1 - (t1 ** 2) - (t2 ** 2)
            for k in range(0, len(right_y)):
                if right_y[k] == 1:
                    cr_plus += 1
                else:
                    cr_minus += 1
            t1 = (cr_plus / (cr_plus + cr_minus))
            t2 = (cr_minus / (cr_plus + cr_minus))
            u_right_y = 1 - (t1 ** 2) - (t2 ** 2)
            pl = (cl_plus + cl_minus) / (c_plus + c_minus)
            pr = (cr_plus + cr_minus) / (c_plus + c_minus)
            gain = u_y - (pl * u_left_y) - (pr * u_right_y)
            return gain
        # we hit leaf node
        # don't have any gain, and don't want to divide by 0
        else:
            return 0


class RandomForestClassifier():
    """
    Random Forest Classifier. Build a forest of decision trees.
    Use this forest for ensemble predictions

    YOU WILL NEED TO MODIFY THE DECISION TREE VERY SLIGHTLY TO HANDLE FEATURE BAGGING

    Parameters:
    -----------
    n_trees: int
            Number of trees in forest/ensemble
    max_features: int
            Maximum number of features to consider for a split when feature bagging
    max_depth: int
            Maximum depth of any decision tree in forest/ensemble
    """

    def __init__(self, n_trees, max_features, max_depth):
        self.n_trees = n_trees
        self.max_features = max_features
        self.max_depth = max_depth

        ##################
        # YOUR CODE HERE #
        ##################
        # make n trees

    # fit all trees

    def fit(self, X, y):
        bagged_X, bagged_y = self.bag_data(X, y)
        print('Fitting Random Forest...\n')
        self.forest = []
        for i in range(self.n_trees):
            print(i+1, end='\t\r')
            ##################
            # YOUR CODE HERE #
            ##################
            x = DecisionTreeClassifier(max_depth=self.max_depth)
            x.num_classes = len(set(bagged_y[i]))
            x.root = x.build_tree(
                bagged_X[i], bagged_y[i], depth=1, features=self.max_features)
            self.forest.append(x)
            #preds_train = x.predict(bagged_X[i])

            #train_accuracy = x.accuracy_score([preds_train], bagged_y[i])

            #print('Train {} {}'.format(i, train_accuracy))

            ##################
        print('Trees have been built!')

    def bag_data(self, X, y, proportion=1.0):
        bagged_X = []
        bagged_y = []
        for i in range(self.n_trees):
            ##################
            # YOUR CODE HERE #
            ##################
            temp_X = []
            temp_y = []
            for j in range(0, 2097):
                idx = random.randint(0, 2097)
                temp_X.append(X[idx])
                temp_y.append(y[idx])
            bagged_X.append(temp_X)
            bagged_y.append(temp_y)
        ##################
        # ensure data is still numpy arrays
        return np.array(bagged_X), np.array(bagged_y)

    def predict(self, X):

        # remove this one \/
        #preds = np.ones(len(X)).astype(int)
        # ^that line is only here so the code runs

        ##################
        # YOUR CODE HERE #
        ##################
        preds = []
        pred_sum = []
        for tree in self.forest:
            pred_sum.append(tree.predict(X))

        for i in range(len(pred_sum[0])):
            right = 0
            wrong = 0
            for example in pred_sum:
                if example[i] == 1:
                    right += 1
                else:
                    wrong += 1

            if right >= wrong:
                preds.append(1)
            else:
                preds.append(0)

        return preds


################################################
# YOUR CODE GOES IN ADABOOSTCLASSIFIER         #
# MUST MODIFY THIS EXISTING DECISION TREE CODE #
################################################
class AdaBoostClassifier():
    def __init__(self):
        pass


sns.set()


def load_data(rootdir='./'):
    x_train = np.loadtxt(rootdir+'x_train.csv', delimiter=',').astype(int)
    y_train = np.loadtxt(rootdir+'y_train.csv', delimiter=',').astype(int)
    x_test = np.loadtxt(rootdir+'x_test.csv', delimiter=',').astype(int)
    y_test = np.loadtxt(rootdir+'y_test.csv', delimiter=',').astype(int)
    y_train[y_train == -1] = 0
    y_test[y_test == -1] = 0
    return x_train, y_train, x_test, y_test


def load_dictionary(rootdir='./'):
    county_dict = pd.read_csv(rootdir+'county_facts_dictionary.csv')
    return county_dict


def dictionary_info(county_dict):
    for i in range(county_dict.shape[0]):
        print('Feature: {} - Description: {}'.format(i,
                                                     county_dict['description'].iloc[i]))


def accuracy_score(preds, y):
    accuracy = (preds == y).sum()/len(y)
    return accuracy


def f1(y, yhat):
    return f1_score(y, yhat)


###########################################################################
# you may add plotting or data processing functions (etc) in here if desired
###########################################################################

