import random
import numpy
from library import funs
from library.funs import parameters_as_string, print_plot, calculate_results_table

from mlp.NeuralNetwork import NeuralNetwork


def task_2():
    epochs = 500
    hidden_nodes = 2
    learning_rate = 0.2
    momentum = 0.9
    bias = True
    network = NeuralNetwork(input_nodes=4, hidden_nodes=hidden_nodes, output_nodes=4,
                            learning_rate=learning_rate,
                            momentum=momentum, bias=bias, epochs=epochs)

    input_list = [1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]
    output = [1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0], [0, 0, 0, 1]

    x = numpy.zeros(epochs * 4, dtype=int)
    for i in range(epochs):
        x[i] = 0
        x[i + epochs] = 1
        x[i + epochs * 2] = 2
        x[i + epochs * 3] = 3

    random.shuffle(x)

    for e in range(len(x)):
        network.train_manual_epochs(input_list[(x[e])], output[(x[e])], e)

    fin = []
    query_list = []
    for i in range(64):
        query_list.append(input_list[x[i]])
        fin.append(network.query(query_list[i]))

    numpy.set_printoptions(suppress=True)  # avoid e-05 notation
    print(output)

    for elem in range(len(fin)):
        print(fin[elem])

    result_tab = numpy.zeros(shape=(len(input_list), len(input_list)))

    for i in range(len(fin)):
        result_tab[numpy.argmax(query_list[i])][numpy.argmax(fin[i])] += 1

    print('Ex 1 results table')
    print(result_tab)
    parameters = parameters_as_string(hidden_nodes, learning_rate, momentum, epochs, bias)
    funs.print_plot(network.sampling_iteration, network.errors_for_plot, 'Zbiór: ćwiczenie\n Wykres zależności wartości błędu od ilości iteracji\n' + parameters)