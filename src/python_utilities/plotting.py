import matplotlib.pyplot as plt


def plot_results(results, plot_title: str):
    plt.figure()
    plt.title(plot_title)
    colors = ['blue', 'firebrick', 'yellow', 'pink']
    plt.plot(results[0], results[1], 'o', c=colors[0])
    plt.xlabel("Elements amount")
    plt.ylabel("Execution time")
    plt.show()


if __name__ == '__main__':
    data = ([], [])
    file_names = ["../../benchmarking/advancedSort.txt",
                  "../../benchmarking/initialTripleSearch.txt",
                  "../../benchmarking/naiveSorting.txt"]
    for name in file_names:
        with(open(name, newline='\n')) as f:
            lines = iter(f)
            title = next(lines)
            print("Title: ", title, end="")
            for line in lines:
                try:
                    x = int(line)
                    y = float(next(lines))
                except:
                    break
                data[0].append(x)
                data[1].append(y)
        plot_results(data, title)
